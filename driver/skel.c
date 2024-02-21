#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/platform_device.h>
#include <linux/freezer.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-event.h>
#include <media/v4l2-device.h>
//#include <media/videobuf2-vmalloc.h>
#include<stdbool.h>

#include "driver_v4l2.h"

MODULE_DESCRIPTION("V4L2 Skeleton Driver");
MODULE_LICENSE("GPL");

struct dev_data {
	struct platform_device	*pdev;
	struct v4l2_device		v4l2_dev;
	struct video_device		vdev;
	struct mutex			mutex;
	u32					pixelformat;
	struct v4l2_fract		timeperframe;
	spinlock_t				s_lock;
	int					input;
	unsigned int			f_count;
	unsigned int			width, height, pixelsize;
};

static void p_release(struct device *dev)
{
	dev_info(dev, "%s: release", __func__);
}

static struct platform_device p_device = {
	.name		= KBUILD_MODNAME,
	.id		= PLATFORM_DEVID_NONE,
	.dev		= {
			.release		= p_release,
	},
};



static int vidioc_querycap(struct file *file, void  *priv, struct v4l2_capability *cap)
{
	struct dev_data *dev = video_drvdata(file);

	strcpy(cap->driver, KBUILD_MODNAME);
	strcpy(cap->card, KBUILD_MODNAME);
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s", dev->v4l2_dev.name);
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE | V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	pr_alert("\nInside querycap");

	return 0;
}

static int vidioc_enum_fmt_vid_cap(struct file *file, void *priv, struct v4l2_fmtdesc *f)
{ 
	pr_alert("\nInside enum_fmt");
	
	if (f->index)
		return -EINVAL;

	strscpy(f->description, "NV12", sizeof(f->description));
	pr_alert("\nDescription set as: %s", f->description);
	f->pixelformat = V4L2_PIX_FMT_NV12;


	return 0;
	
	
	
}

static int vidioc_g_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *f)
{
	
	struct dev_data *dev = video_drvdata(file);
	
	pr_alert("\nInside g_fmt");
	f->fmt.pix.width = dev->width = F_DATA.width;
	f->fmt.pix.height = dev->height = F_DATA.height;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.pixelformat = dev->pixelformat;
	f->fmt.pix.bytesperline = f->fmt.pix.width * dev->pixelsize;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	return 0;
}

static int vidioc_try_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *f)
{
	
	struct dev_data *dev = video_drvdata(file);
	pr_alert("\nInside try_fmt");
	if (f->fmt.pix.pixelformat != V4L2_PIX_FMT_NV12)
		v4l2_err(&dev->v4l2_dev, "%s: Unknown format..\n", __func__);

	dev->input = 0;
	f->fmt.pix.pixelformat = dev->pixelformat = V4L2_PIX_FMT_NV12;
	dev->pixelsize = 460800; //was 2
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	if ((f->fmt.pix.width != F_DATA.width) || (f->fmt.pix.height != F_DATA.height))
		v4l2_info(&dev->v4l2_dev, "%s pixel width and height changed to default\n", __func__);

	f->fmt.pix.width = dev->width = F_DATA.width;
	f->fmt.pix.height = dev->height = F_DATA.height;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.bytesperline = dev->width * dev->pixelsize;
	f->fmt.pix.sizeimage = dev->height * f->fmt.pix.bytesperline;
	return 0;
}

static int vidioc_s_fmt_vid_cap(struct file *file, void *priv, struct v4l2_format *f)
{
	
	struct dev_data *dev = video_drvdata(file);
	pr_alert("\nInside s_fmt");
	vidioc_try_fmt_vid_cap(file, priv, f);

	return 0;
}

static const struct v4l2_ioctl_ops skel_ioctl_ops = {
	.vidioc_querycap		= vidioc_querycap,
	.vidioc_enum_fmt_vid_cap	= vidioc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= vidioc_g_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= vidioc_s_fmt_vid_cap,
	};

static const struct v4l2_file_operations skel_fops = {
	.owner				= THIS_MODULE,
	.open				= v4l2_fh_open,
	.unlocked_ioctl		= video_ioctl2,
};

static int p_probe(struct platform_device *pdev)
{
	struct dev_data *dev;
	struct video_device *vdev;
	int ret;
	printk("check1");
	dev_info(&pdev->dev, "%s: probe function\n", __func__);
	dev = devm_kzalloc(&pdev->dev, sizeof(struct dev_data), GFP_KERNEL);
	printk("check2");
	if (!dev)
		return -ENOMEM;
	dev->pdev = pdev;
	dev_set_drvdata(&pdev->dev, dev);

	ret = v4l2_device_register(&pdev->dev, &dev->v4l2_dev);
	if (ret) 
	{
		dev_err(&pdev->dev, "%s: v4l2 device registration failed..\n", __func__);
		return ret;
	}
	printk("check3");
	dev->pixelformat = V4L2_PIX_FMT_NV12;
	dev->timeperframe = (struct v4l2_fract) {1, F_DATA.framerate};
	dev->width = F_DATA.width;
	dev->height = F_DATA.height;
	dev->pixelsize = 460800; //was 2
	dev->input = 0;
	
	vdev = &dev->vdev;
	strscpy(vdev->name, KBUILD_MODNAME, sizeof(vdev->name));
	vdev->release = video_device_release_empty;
	vdev->fops = &skel_fops;
	vdev->ioctl_ops = &skel_ioctl_ops;
	vdev->v4l2_dev = &dev->v4l2_dev;
	vdev->lock = &dev->mutex;
	vdev->device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	video_set_drvdata(vdev, dev);
	printk("check4");
	ret = video_register_device(vdev, VFL_TYPE_VIDEO, -1);
	printk("check5");
	
	if (ret < 0) 
	{
		dev_err(&pdev->dev, "%s: video device registration failed..\n", __func__);
		v4l2_device_unregister(&dev->v4l2_dev);
		video_device_release(&dev->vdev);
		return ret;
	}
	
	printk("check6");
	v4l2_info(&dev->v4l2_dev, "%s: V4L2 device registered as %s\n", __func__, video_device_node_name(vdev));
	return 0;
}

static int p_remove(struct platform_device *pdev)
{
	struct dev_data *dev;

	dev_info(&pdev->dev, "%s: Remove function\n", __func__);
	dev = platform_get_drvdata(pdev);
	v4l2_info(&dev->v4l2_dev, "%s: Unregistering driver%s\n", __func__, video_device_node_name(&dev->vdev));
	video_unregister_device(&dev->vdev);
	v4l2_device_unregister(&dev->v4l2_dev);
	return 0;
}

static struct platform_driver p_driver = {
	.probe = p_probe,
	.remove = p_remove,
	.driver = {
		.name = KBUILD_MODNAME,
		.owner = THIS_MODULE,
	},
};

static int __init v4l2_init(void)
{
	int ret;

	pr_info("%s: Inserting V4L2 driver module\n", __func__);

	ret = platform_device_register(&p_device);
	
	
	if (ret) 
	{
		pr_err("%s: Registration of platform device %s failed..\n", __func__, p_device.name);
		return ret;
	}
	
	ret = platform_driver_register(&p_driver);
	
	if (ret) 
	{
		pr_err("%s: Registration of platform driver %s failed..\n", __func__, p_driver.driver.name);
		platform_device_unregister(&p_device);
	}
	
	pr_info("Registering V4L2 driver module\n");
	return ret;
}	

static void __exit v4l2_exit(void)
{
	pr_info("%s: Removing V4L2 driver module\n", __func__);
	platform_driver_unregister(&p_driver);
	platform_device_unregister(&p_device);
}

module_init(v4l2_init);
module_exit(v4l2_exit);

