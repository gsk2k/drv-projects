#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int dest[40][30] = {0};
pthread_mutex_t lock;

typedef struct param{
    int *src;
    int *dst;
    int src_x;
    int src_y;
    int dst_x;
    int dst_y;
    int x_offset; //dest width offest
    int y_offset; //dest height offset
}param;


int cpy (param *pptr)
{
    if(pptr->x_offset<pptr->dst_x && pptr->y_offset<pptr->dst_y){
        int *element;
        for (int row=0; row<pptr->src_y; row++){
            element = pptr->dst + pptr->dst_x*(pptr->y_offset + row) + pptr->x_offset;
            for (int col=0; col<pptr->src_x; col++){
//                    (*((pptr->dst+(i+pptr->x_offset))+(j+pptr->y_offset))) = (*(pptr->src+i*pptr->src_x+j));
                *(element+col) = (*(pptr->src+row*pptr->src_x+col));
            }
        }
    }
    else{
        printf("Source array dimensions greater than what destination can accommodate\n");
        return -1;
    }
    return 0;
}

void *mp1_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr1[10][10] = {0};
    int cnt = 0;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr1[row][col] = cnt++;
        }
    }
    pptr.src = *arr1;
    pptr.x_offset = 0;      //choose starting row for arr1 cpy
    pptr.y_offset = 0;      //choose starting column for arr1 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}


void *mp2_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr2[10][10] = {0};
    int cnt = 100;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr2[row][col] = cnt++;
        }
    }
    pptr.src = *arr2;
    pptr.x_offset = 10;      //choose starting row for arr2 cpy
    pptr.y_offset = 0;      //choose starting column for arr2 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp3_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr3[10][10] = {0};
    int cnt = 200;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr3[row][col] = cnt++;
        }
    }
    pptr.src = *arr3;
    pptr.x_offset = 20;      //choose starting row for arr3 cpy
    pptr.y_offset = 0;      //choose starting column for arr3 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp4_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr4[10][10] = {0};
    int cnt = 300;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr4[row][col] = cnt++;
        }
    }
    pptr.src = *arr4;
    pptr.x_offset = 0;      //choose starting row for arr4 cpy
    pptr.y_offset = 10;      //choose starting column for arr4 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp5_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr5[10][10] = {0};
    int cnt = 400;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr5[row][col] = cnt++;
        }
    }
    pptr.src = *arr5;
    pptr.x_offset = 10;      //choose starting row for arr5 cpy
    pptr.y_offset = 10;      //choose starting column for arr5 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp6_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr6[10][10] = {0};
    int cnt = 500;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr6[row][col] = cnt++;
        }
    }
    pptr.src = *arr6;
    pptr.x_offset = 20;      //choose starting row for arr6 cpy
    pptr.y_offset = 10;      //choose starting column for arr6 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp7_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr7[10][10] = {0};
    int cnt = 600;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr7[row][col] = cnt++;
        }
    }
    pptr.src = *arr7;
    pptr.x_offset = 0;      //choose starting row for arr7 cpy
    pptr.y_offset = 20;      //choose starting column for arr7 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp8_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr8[10][10] = {0};
    int cnt = 700;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr8[row][col] = cnt++;
        }
    }
    pptr.src = *arr8;
    pptr.x_offset = 10;      //choose starting row for arr8 cpy
    pptr.y_offset = 20;      //choose starting column for arr8 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp9_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr9[10][10] = {0};
    int cnt = 800;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr9[row][col] = cnt++;
        }
    }
    pptr.src = *arr9;
    pptr.x_offset = 20;      //choose starting row for arr9 cpy
    pptr.y_offset = 20;      //choose starting column for arr9 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp10_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr10[10][10] = {0};
    int cnt = 900;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr10[row][col] = cnt++;
        }
    }
    pptr.src = *arr10;
    pptr.x_offset = 0;      //choose starting row for arr10 cpy
    pptr.y_offset = 30;      //choose starting column for arr10 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp11_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr11[10][10] = {0};
    int cnt = 1000;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr11[row][col] = cnt++;
        }
    }
    pptr.src = *arr11;
    pptr.x_offset = 10;      //choose starting row for arr11 cpy
    pptr.y_offset = 30;      //choose starting column for arr11 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *mp12_fill(void *vargp)
{
    param pptr;
    pptr.dst = *dest;
    pptr.src_x = 10;
    pptr.src_y = 10;
    pptr.dst_x = 30;
    pptr.dst_y = 40;
    int arr12[10][10] = {0};
    int cnt = 1100;
    for (int row = 0; row<10; row++){
        for (int col = 0; col<10; col++){
            arr12[row][col] = cnt++;
        }
    }
    pptr.src = *arr12;
    pptr.x_offset = 20;      //choose starting row for arr12 cpy
    pptr.y_offset = 30;      //choose starting column for arr12 cpy
    sleep(1);
    pthread_mutex_lock(&lock);
    cpy(&pptr);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{

//	int arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
//	int n = sizeof(arr);
//  pptr.x_offset = 2;      //choose starting row
//  pptr.y_offset = 2;      //choose starting column
//	pptr.src = *arr;

/*
    pthread_t id1, id2, id3, id4, id5, id6, id7, id8, id9, id10, id11, id12;

    printf("\nArray 1 copy start\n");
    pthread_create(&id1, NULL, mp1_fill, NULL);
//    pthread_join(id1, NULL);
    printf("Array 1 copy complete\n");

    printf("\nArray 2 copy start\n");
    pthread_create(&id2, NULL, mp2_fill, NULL);
//    pthread_join(id2, NULL);
    printf("Array 2 copy complete\n");

    printf("\nArray 3 copy start\n");
    pthread_create(&id3, NULL, mp3_fill, NULL);
//    pthread_join(id3, NULL);
    printf("Array 3 copy complete\n");

    printf("\nArray 4 copy start\n");
    pthread_create(&id4, NULL, mp4_fill, NULL);
//    pthread_join(id4, NULL);
    printf("Array 4 copy complete\n");

    printf("\nArray 5 copy start\n");
    pthread_create(&id5, NULL, mp5_fill, NULL);
//    pthread_join(id5, NULL);
    printf("Array 5 copy complete\n");

    printf("\nArray 6 copy start\n");
    pthread_create(&id6, NULL, mp6_fill, NULL);
//    pthread_join(id6, NULL);
    printf("Array 6 copy complete\n");

    printf("\nArray 7 copy start\n");
    pthread_create(&id7, NULL, mp7_fill, NULL);
//    pthread_join(id7, NULL);
    printf("Array 7 copy complete\n");

    printf("\nArray 8 copy start\n");
    pthread_create(&id8, NULL, mp8_fill, NULL);
//    pthread_join(id8, NULL);
    printf("Array 8 copy complete\n");

    printf("\nArray 9 copy start\n");
    pthread_create(&id9, NULL, mp9_fill, NULL);
//    pthread_join(id9, NULL);
    printf("Array 9 copy complete\n");

    printf("\nArray 10 copy start\n");
    pthread_create(&id10, NULL, mp10_fill, NULL);
//    pthread_join(id10, NULL);
    printf("Array 10 copy complete\n");

    printf("\nArray 11 copy start\n");
    pthread_create(&id11, NULL, mp11_fill, NULL);
//    pthread_join(id11, NULL);
    printf("Array 11 copy complete\n");

    printf("\nArray 12 copy start\n");
    pthread_create(&id12, NULL, mp12_fill, NULL);
//    pthread_join(id12, NULL);
    printf("Array 12 copy complete\n");
*/

    pthread_t id[12];
    void (*mp_fill[12])(void*) = {mp1_fill, mp2_fill, mp3_fill, mp4_fill, mp5_fill, mp6_fill, mp7_fill, mp8_fill, mp9_fill, mp10_fill, mp11_fill, mp12_fill};
    for (int i = 0; i<12; i++){
        pthread_create(&id[i], NULL, mp_fill[i], NULL);
    }
    for (int i = 0; i<12; i++){
        pthread_join(id[i], NULL);
    }
//	cpy(&pptr);

    pthread_mutex_destroy(&lock);

    printf("\nCopied array is:\n");
    for (int i=0; i<40; i++){
        for (int j=0; j<30; j++){
            printf("0x%03x  ", dest[i][j]);
        }
        printf("\n");
    }
    return 0;
}
