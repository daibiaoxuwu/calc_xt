#include<cstdio>
#include<cstring>
#include<map>
#include <ctime>
#include <vector>
#include <cassert>
#include <set>
#include <queue>
#include <cmath>

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
    int remain_sum = 0; for (int i : known_remain_cnt) remain_sum += i;
    int dora[34]; for (int i = 0; i < 34; ++ i) fscanf(fin,"%d", &dora[i]);
    fclose(fin);

    int init_xt = calc_xt(hand_cnt);
    printf("%d\n",init_xt);

    std::set<std::array<int,34>> nodes[7]; //TODO: do not need this set
    std::map<std::array<int,34>, int> cntmap;
    std::vector<std::vector<std::pair<int,int>>> roadmap;
    int cnt = 0;
    for (int i = 0; i < 34; ++i) {
        if(hand_cnt[i]>0){
            hand_cnt[i]--;
            nodes[calc_xt(hand_cnt)].insert(hand_cnt);
            cntmap[hand_cnt]=cnt;
            roadmap.emplace_back(std::vector<std::pair<int,int>>());
            cnt++;
            hand_cnt[i]++;
        }
    }

    for (int xt = min(6,init_xt+1); xt > 1; --xt) {
        /*while(nodes[xt].size()<maxsize)*/{
            auto iternodes = nodes[xt];
            for (auto hand : iternodes) {
                int roadcnt = cntmap[hand];
                for (int i = 0; i < 34; ++i) {
                    hand[i]++;
                    /*if (calc_xt(hand) < xt)*/ {
                        for (int j = 0; j < 34; ++j) {
                            if (j == i)continue;
                            if (hand[j] > 0) {
                                hand[j]--;
                                int xt2 = calc_xt(hand);
                                if (xt2 <= xt) {//TODO <=
                                    if (nodes[xt2].count(hand) == 0) {
                                        cntmap[hand] = cnt;
                                        roadmap[roadcnt].emplace_back(std::make_pair(cnt,i));
                                        roadmap.emplace_back(std::vector<std::pair<int,int>>{ std::make_pair(roadcnt,j)});
                                        cnt++;
                                        nodes[xt2].insert(hand);
                                    }
                                }
                                hand[j]++;
                            }
                        }
                    }
                    hand[i]--;
                }
            }
            printf("%d len: %d %d\n",xt,nodes[xt].size(),nodes[xt-1].size());
        }
    }
    printf("cnt:%d\n",cnt);

    const int Remain_Round = max(6, 13 - round);
    const double* Remain_Prob = round_prob + (18 - Remain_Round);

    auto valmap = new double*[cnt];
    for (int l = 0; l < cnt; ++l) {
        valmap[l] = new double[Remain_Round];
        memset(valmap[l],0,Remain_Round * sizeof(double));
    }

    auto dvals = new double[cnt];
    memset(dvals, 0, cnt*sizeof(double));
    auto mvrate = new double[cnt];
    memset(mvrate, 0, cnt*sizeof(double));
    std::priority_queue<std::pair<double, int>> queue;
    const int DECIDE_ROUND = 10.0;

    for (auto hand : nodes[1]) {
        int ting_cnt = 0;
        for (int i = 0; i < 34; ++i) {
            hand[i]++;
            if (calc_xt(hand) == 0) ting_cnt += known_remain_cnt[i]; //TODO: known_remain_cnt
            hand[i]--;
        }
        assert(ting_cnt > 0);
        assert(cntmap.count(hand) > 0);
        double val = ting_cnt / (double)remain_sum;
        int roadcnt = cntmap[hand];
        valmap[roadcnt][0] = val;
        double dval = val * Remain_Prob[0];
        for (int j = 1; j < Remain_Round; ++j) {
            double val2 = valmap[roadcnt][j-1] * (1 - val);
            assert(val2 > 0 && val2 < 1);
            valmap[roadcnt][j] = val2;
            dval += val2 * Remain_Prob[j];
            assert(dval > 0 && dval < 1);
        }
        dvals[roadcnt] = dval;
        queue.emplace(std::make_pair(dval, roadcnt));
    }

    int minqueue = 1000000;

    while (!queue.empty()) {
        auto top = queue.top();
        if(top.second < 9) break;
        if(top.first != dvals[top.second]){
            assert(top.first < dvals[top.second]);
            queue.pop();
            continue;
        }
        for (auto i : roadmap[top.second]) {
            if (minqueue > i.first){
                minqueue = i.first; printf("queue:%d\n",minqueue);
            }
            if(i.first < 9){
                printf("visit:%d\n",i.first);
            }
            if (dvals[i.first] < top.first) {
                double olddval = dvals[i.first];
                //calculate new dval
                double tval = known_remain_cnt[i.second] / (double) remain_sum;
                mvrate[i.first] += tval;
                if(!(mvrate[i.first] >= 0 && mvrate[i.first] < 1)){
                    printf("mverror:%d %lf %lf",i.first,mvrate[i.first],tval);
                }
                assert(mvrate[i.first] >= 0 && mvrate[i.first] < 1);
                double stayrate = 1 - mvrate[i.first];
                double strate = 1;
                double dval = 0;
                for (int j = 1; j < Remain_Round; ++j) { //hu@j round = arrive@(j-k)round + hu@k round
                    for (int k = j - 1; k >= 0; --k) {
                        valmap[i.first][j] += valmap[top.second][k] * tval * strate;
                        if(!(valmap[i.first][j] >= 0 && valmap[i.first][j] < 1)){
                            printf("valerror: %d %d %lf\n",i.first,j,valmap[i.first][j]);
                        }
                        strate *= stayrate;
                    }
                    dval += valmap[i.first][j] * Remain_Prob[j];
                }
                dvals[i.first] = dval;
                /*
                if(dval >= top.first){
                    printf("dval upper:%d %d %lf -> %lf %lf\n new:",i.first,top.second,olddval,dval,top.first);
                    for (int j = 0; j < Remain_Round; ++j) {
                        printf("%lf ",valmap[i.first][j]);
                    }
                    printf("\n");
                    for (int j = 0; j < Remain_Round; ++j) {
                        printf("%lf ",valmap[top.second][j]);
                    }
                    printf("\n");
                }*/
                if(!(dval >= 0 && dval < 1))printf("%d %lf\n",i.first, dval);
                assert(dval >= 0 && dval < 1);
                if(i.first == 1164)printf("1164!%lf\n",dval);
                queue.emplace(std::make_pair(dval, i.first));
            }
        }

        while (queue.top() != top){
            auto top2 = queue.top();
            printf("error: %d %lf %d %lf %d\n",queue.size(),top.first, top.second, top2.first, top2.second);
            queue.pop();
        }
        queue.pop();
    }
    int lastcnt = 0;
    for (int i = 0; i < 34; ++i) {
        if(hand_cnt[i]>0){
            printf("card: %s ",mname[i]);
            printf("dval: %lf ",dvals[lastcnt]);
            printf("valmap: ");
            for (int j = 0; j < Remain_Round; ++j) {
                printf("%d ",int(valmap[lastcnt][j]*1000000));
            }
            printf("\n");
            lastcnt++;
        }
    }

    return 0;

}
