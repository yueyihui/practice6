#include <stdio.h>
#include <string.h>    
#include <stdlib.h>
#include <time.h>

#define F 4
#define P 10
#define INT_ARRAY_SIZE(x, type) (sizeof(x)/sizeof(type))

void FIFO(int*);
void LRU(int*);
int* generate_RS();

typedef struct practice6_t {
    int mtime;
    int m;
    int prior;//first in will get small number
} PHY_MEM, *PHY_MEMP;
PHY_MEMP quicksort(PHY_MEMP a, int low, int high);

int main(int argc, const char *argv[])
{
    if (!strcmp(argv[1], "FIFO")) {
        FIFO(generate_RS());
    } else if (!strcmp(argv[1], "LRU")) {
        LRU(generate_RS());
    } else {
        printf("%s\n", "please input practice6 FIFO or LRU");
    }
    return 0;
}

void FIFO(int *rs)
{
    int page_swap_count = 0;

    PHY_MEM ddr[F]; 
    for (int i = 0; i < F; i++) {
         ddr[i].m = -1;
         ddr[i].prior = -1;
    }

    for (int rs_index = 0; rs_index < P; rs_index++) {
        for (int f = 0; f < F; f++) {
            if (ddr[f].m == rs[rs_index]) {
                goto skip;
            }
            if (ddr[f].prior == -1) {
                ddr[f].m = rs[rs_index];
                ddr[f].prior = rs_index;
                goto skip;
            }
        }

        quicksort(ddr, 0, F - 1);//ddr.prior now example 0 1 2 3
        ddr[0].prior = ddr[F-1].prior + 1;//ddr.prior now example 3+1 1 2 3
        ddr[0].m = rs[rs_index];
        page_swap_count++;

skip:
        continue;
    }

    printf("rate of page missing %lf", (double)page_swap_count / (double)P);
    free(rs);
}

void LRU(int *rs)
{
    free(rs);
}

int* generate_RS()
{
    int range = P * sizeof(int);
    int *rs = (int*)malloc(range);
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        rs[i] = rand() % 10;//random 0~9
        printf("%d ", rs[i]);
    }
    printf("\n");
    return rs;
}

PHY_MEMP quicksort(PHY_MEMP ddr, int low, int high)
{
    int i = low;
    int j = high;
    PHY_MEM key = ddr[low];

    if (low >= high)
    {
        return ddr;
    }

    while (low < high)
    {
        while (low < high && key.prior <= ddr[high].prior)
        {
            --high;
        }
        if (key.prior > ddr[high].prior)
        {
            ddr[low] = ddr[high];
            ++low;
        }
        while (low < high && key.prior >= ddr[low].prior)
        {
            ++low;
        }
        if (key.prior < ddr[low].prior)
        {
            ddr[high] = ddr[low];
            --high;
        }
    }

    ddr[low] = key;
    quicksort(ddr, i, low-1);
    quicksort(ddr, low+1, j);

    return ddr;
}

