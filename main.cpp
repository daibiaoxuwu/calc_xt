#include<cstdio>
#include<cstring>
#include<map>
#include <ctime>
#include <vector>
#include <cassert>
#include <set>

FILE* fin, *fout, *flog;
inline void maxer(int &x, int y) { if (y > x) x = y; }
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
const double round_prob[19] = {1.000000, 1.000000, 0.999708, 0.998029, 0.991947, 0.976532, 0.946340, 0.897968, 0.831425, 0.750198, 0.660036, 0.567684, 0.479381, 0.399071, 0.329266, 0.270215, 0.221551, 0.182120, 0.00000};
const long long C[5][5] = {{1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}};
const char* mname[]={" 1W", " 2W", " 3W", " 4W", " 5W", " 6W", " 7W", " 8W", " 9W", " 1B", " 2B", " 3B", " 4B", " 5B", " 6B", " 7B", " 8B", " 9B", " 1T", " 2T", " 3T", " 4T", " 5T", " 6T", " 7T", " 8T", " 9T", "EST", "STH", "WST", "NTH", "BAI", " FA", "ZHO"};
const int f_len3 = 15, MX = 16000,MAX_HU_VALUE = 6,CHILD_NUM = 10;
unsigned long long f[16][2][f_len3][MX];
int dppath[MX][5][CHILD_NUM];
int dpxt[MX];
double fact[136];
int tot;

int calc_xt(const std::array<int,34> hand_cnts){
    int ha_cursor = MAX_HU_VALUE+1;
    for (int i = 0; i < 34; ++i) {
        int piece = (i > 27 ? 9 : i % 9);
        ha_cursor = dppath[ha_cursor][hand_cnts[i]][piece];
    }
    return dpxt[ha_cursor];
}
int main() {
    FILE* fdp = fopen("D:\\workspace\\mahjong_old\\calc_automation\\cmake-build-debug\\automation_xt2.txt", "r");
    fscanf(fdp,"%d",&tot);
    printf("tot:%d\n",tot);
    for(int i = 1; i <= tot; ++i){
        for (int ci = 0; ci < 5; ++ci) {
            for (int cj = 0; cj < CHILD_NUM; ++cj) {
                fscanf(fdp, "%d", &dppath[i][ci][cj]);
            }
        }
    }
    for(int i = 1; i <= tot; ++i){
        fscanf(fdp, "%d", &dpxt[i]);
    }
    fclose(fdp);

    fin = fopen("input.txt","r");
    int rest_num; fscanf(fin,"%d", &rest_num);
    int round = 18 - rest_num / 4;//start with 69 -> 1.end with 0 - 18.
    std::array<int,34> hand_cnt{}; for (int i = 0; i < 34; ++ i) fscanf(fin, "%d", &hand_cnt[i]);
    int known_remain_cnt[34]; for (int i = 0; i < 34; ++ i) fscanf(fin,"%d", &known_remain_cnt[i]);
    int dora[34]; for (int i = 0; i < 34; ++ i) fscanf(fin,"%d", &dora[i]);
    fclose(fin);

    int init_xt = calc_xt(hand_cnt);
    printf("%d\n",init_xt);

    std::set<std::array<int,34>> nodes[7][2];
    for (int i = 0; i < 34; ++i) {
        if(hand_cnt[i]>0){
            hand_cnt[i]--;
            nodes[calc_xt(hand_cnt)][0].insert(hand_cnt);
            hand_cnt[i]++;
        }
    }

    int maxsize = 100;
    for (int xt = init_xt; xt > 0; --xt,maxsize *= 10) {
        unsigned nw = 0;
        while(nodes[xt][nw].size()<maxsize){
            nodes[xt][nw&1u]=nodes[xt][nw];
            nodes[xt-1][nw&1u]=nodes[xt-1][nw];
            for (auto hand : nodes[xt][nw]) {
                for (int i = 0; i < 34; ++i) {
                    printf("i:%d\n",i);
                    if(hand[i]==4)continue;
                    hand[i]++;
                    /*if (calc_xt(hand) < xt)*/ {
                        for (int j = 0; j < 34; ++j) {
                            if(j==i)continue;
                            if (hand[j] > 0) {
                                hand[j]--;

                                int xt2 = calc_xt(hand);
                                if (xt2 <= xt)
                                {
                                    nodes[xt2][nw&1u].insert(hand);
                                }
                                hand[j]++;
                            }
                        }
                    }
                    hand[i]--;
                }
            }
            printf("%d len: %d %d\n",xt,nodes[xt][nw&1u].size(),nodes[xt-1][nw&1u].size());
            nw=1-nw;
        }
    }

    return 0;

}
