#include <stdio.h>
#include <math.h>

#define INPUT_FILE "city_mcepdata/city011/city011_"
#define DATASET_FILE "city_mcepdata/city021/city021_"
#define PICTURE_PATH "pic1.ppm"
#define DATASET_NUM_MAX 100
#define DATASET_FRAME_MAX 200
#define DATASET_DIMENSION_MAX 15

#define TATE_YOKO_COST 1
#define NANAME_COST 2

// 局所距離を求める関数
double d_calc(int dataset_num, int input_num, int x, int y);

double dataset[DATASET_NUM_MAX][DATASET_FRAME_MAX][DATASET_DIMENSION_MAX];
double input_data[DATASET_NUM_MAX][DATASET_FRAME_MAX][DATASET_DIMENSION_MAX];
int dataset_frame[DATASET_NUM_MAX];
int input_frame[DATASET_NUM_MAX];

int main(void)
{
    unsigned char dumy[1000];
    unsigned char file_name[1000];
    // テンプレートのファイルを開く

    // データセットの取り込み
    for (int i = 0; i < DATASET_NUM_MAX; i++)
    {
        int frame;
        snprintf(file_name, sizeof(file_name), "%s%03d.txt", DATASET_FILE, i + 1);
        FILE *fp;
        fp = fopen(file_name, "r");
        if (fp == NULL)
        {
            printf("%s\n開けませんでした\n", file_name);
            break;
        }

        // 上2つのいらないデータをdumyに流す
        fscanf(fp, "%s", dumy);
        fscanf(fp, "%s", dumy);
        fscanf(fp, "%d", &frame);

        dataset_frame[i] = frame;

        for (int frame_cnt = 0; frame_cnt < frame; frame_cnt++)
        {
            for (int dim_cnt = 0; dim_cnt < DATASET_DIMENSION_MAX; dim_cnt++)
            {
                fscanf(fp, "%lf", &dataset[i][frame_cnt][dim_cnt]);
            }
        }
    }

    // 入力データの読み込み
    for (int i = 0; i < DATASET_NUM_MAX; i++)
    {
        snprintf(file_name, sizeof(file_name), "%s%03d.txt", INPUT_FILE, i + 1);
        FILE *input_fp;
        input_fp = fopen(file_name, "r");

        if (input_fp == NULL)
        {
            printf("INPUTデータが開けませんでした\n");
            return -1;
        }

        int frame;

        // 上2つのいらないデータをdumyに流す
        fscanf(input_fp, "%s", dumy);
        fscanf(input_fp, "%s", dumy);
        fscanf(input_fp, "%d", &frame);

        input_frame[i] = frame;

        for (int frame_cnt = 0; frame_cnt < input_frame[i]; frame_cnt++)
        {
            for (int dim_cnt = 0; dim_cnt < DATASET_DIMENSION_MAX; dim_cnt++)
            {
                fscanf(input_fp, "%lf", &input_data[i][frame_cnt][dim_cnt]);
            }
        }
        fclose(input_fp);
    }

    //正解の個数を入れておく変数
    int correct_cnt = 0; //正解
    int incorrect_cnt = 0; //不正解

    for (int input_data_cnt = 0; input_data_cnt < DATASET_NUM_MAX; input_data_cnt++)
    {
        printf("\n\n%d 処理開始...\n", input_data_cnt + 1);
        double min_data = __DBL_MAX__;
        int min_asc;

        // DPマッチング
        for (int i = 0; i < DATASET_NUM_MAX; i++)
        {

            double dp[dataset_frame[i]][input_frame[input_data_cnt]];

            for (int input_cnt = 0; input_cnt < input_frame[input_data_cnt]; input_cnt++)
            {
                for (int dataset_cnt = 0; dataset_cnt < dataset_frame[i]; dataset_cnt++)
                {
                    double min_cost = __DBL_MAX__;

                    if (input_cnt == 0 && dataset_cnt == 0)
                    {
                        min_cost = d_calc(i, input_data_cnt, input_cnt, dataset_cnt);
                    }

                    if (input_cnt >= 1)
                    {
                        double tmp = dp[dataset_cnt][input_cnt - 1] + d_calc(i, input_data_cnt, input_cnt, dataset_cnt) * TATE_YOKO_COST;
                        if (min_cost >= tmp)
                        {
                            min_cost = tmp;
                        }
                    }
                    if (dataset_cnt >= 1)
                    {
                        double tmp = dp[dataset_cnt - 1][input_cnt] + d_calc(i, input_data_cnt, input_cnt, dataset_cnt) * TATE_YOKO_COST;
                        if (min_cost >= tmp)
                        {
                            min_cost = tmp;
                        }
                    }
                    if (input_cnt >= 1 && dataset_cnt >= 1)
                    {
                        double tmp = dp[dataset_cnt - 1][input_cnt - 1] + d_calc(i, input_data_cnt, input_cnt, dataset_cnt) * NANAME_COST;
                        if (min_cost >= tmp)
                        {
                            min_cost = tmp;
                        }
                    }
                    dp[dataset_cnt][input_cnt] = min_cost;
                }
            }

            if (min_data > dp[dataset_frame[i] - 1][input_frame[input_data_cnt] - 1])
            {
                min_data = dp[dataset_frame[i] - 1][input_frame[input_data_cnt] - 1];
                printf("%d %lf\n", i + 1, min_data);
                min_asc = i;
            }
        }

        if(input_data_cnt == min_asc){
            printf("正解！\n");
            correct_cnt++;
        }
        else{
            printf("不正解 ＿|￣|○\n");
            incorrect_cnt++;
        }
    }

    printf("\n\n総数：%d 正解数：%d 不正解数:%d\n", correct_cnt + incorrect_cnt, correct_cnt, incorrect_cnt);
    printf("正解率：%lf %%\n", (float)correct_cnt / ((float)correct_cnt + (float)incorrect_cnt) * 100);
}

// 局所距離を求める関数
// dataset_num: 使うデータセット x: 横軸 y;縦軸
double d_calc(int dataset_num, int input_num, int x, int y)
{
    double sum = 0;
    for (int i = 0; i < DATASET_DIMENSION_MAX; i++)
    {
        sum += pow(dataset[dataset_num][x][i] - input_data[input_num][y][i], 2);
    }
    return sqrt(sum);
}