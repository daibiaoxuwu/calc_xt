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
int BIG = 10000000;

int calc_xt(const std::array<int,34> hand_cnts){
    int ha_cursor = MAX_HU_VALUE+1;
    for (int i = 0; i < 34; ++i) {
        int piece = (i > 27 ? 9 : i % 9);
        ha_cursor = dppath[ha_cursor][hand_cnts[i]][piece];
    }
    return dpxt[ha_cursor];
}
int main() {
    double MaxVal = 0;
    for (int i1 = 0; i1 < 18; ++i1) { MaxVal += round_prob[i1] * round_prob[i1]; }
    FILE *fdp = fopen("..\\automation_xt2.txt", "r");
    fscanf(fdp, "%d", &tot);
//    printf("tot:%d\n", tot);
    for (int i = 1; i <= tot; ++i) {
        for (int ci = 0; ci < 5; ++ci) {
            for (int cj = 0; cj < CHILD_NUM; ++cj) {
                fscanf(fdp, "%d", &dppath[i][ci][cj]);
            }
        }
    }
    for (int i = 1; i <= tot; ++i) {
        fscanf(fdp, "%d", &dpxt[i]);
    }
    fclose(fdp);

    fin = fopen("input.txt", "r");
    int rest_num;
    fscanf(fin, "%d", &rest_num);
    int round = 18 - rest_num / 4;//start with 69 -> 1.end with 0 - 18.
    std::array<int, 34> hand_cnt{};
    for (int i = 0; i < 34; ++i) fscanf(fin, "%d", &hand_cnt[i]);
    int known_remain_cnt[34];
    for (int i = 0; i < 34; ++i) fscanf(fin, "%d", &known_remain_cnt[i]);
    double remain_sum = 0;
    for (int i : known_remain_cnt) remain_sum += i;
    int dora[34];
    for (int i = 0; i < 34; ++i) fscanf(fin, "%d", &dora[i]);
    fclose(fin);

    int init_xt = calc_xt(hand_cnt);
//    printf("%d\n", init_xt);
    if(init_xt > 3)
        return -1000;

    std::map<std::array<int, 34>, int> cntmap3; //todo: turn to set
    std::map<std::array<int, 34>, int> cntmap4;
    int* xt_limit = new int[BIG];
    auto roadmap3 = new std::array<int, 34>[BIG];
    auto handmap4 = new std::array<int, 34>[BIG];
    auto roadmap4 = new std::array<int, 34>[BIG];
    std::set<int> nodes0;

    //zero: empty. start from 1.
    cntmap4[hand_cnt] = 1;
    handmap4[1] = hand_cnt; //14: cur
    xt_limit[1] = init_xt;
    int cnt4 = 2;
    int cnt3 = 1;
    int current = 1;
    for (; current < cnt4 && cnt3 < BIG - 1000 && cnt4 < BIG - 1000 && nodes0.size() < 250 ; ++current) {
//        if (current % 10000 == 0)printf("curr:%d cnt4:%d cnt3:%d\n", current, cnt4, cnt3, nodes0.size());
        auto hand = handmap4[current];
        for (int i = 0; i < 34; ++i) {
            if (hand[i] > 0) {
                hand[i]--;

                if (cntmap3.count(hand) == 0) {
                    int xt3 = calc_xt(hand);
                    if(cnt3 < BIG && xt3 <= xt_limit[current] + 1) {
                        cntmap3[hand] = cnt3;  //13: cnt3
                        roadmap4[current][i] = cnt3;
                        roadmap3[cnt3][i] = current;

                        for (int j = 0; j < 34; ++j) { //14: cnt4
                            if (j == i)continue;
                            hand[j]++;
                            if (cntmap4.count(hand) == 0) {
                                if(cnt4 < BIG) {
                                    cntmap4[hand] = cnt4;
                                    int xt4 = calc_xt(hand);
                                    xt_limit[cnt4] = min(xt_limit[current], xt4 + 1); //todo xt3 or calcxt?
                                    handmap4[cnt4] = hand;
                                    roadmap3[cnt3][j] = cnt4;
                                    roadmap4[cnt4][j] = cnt3;
                                    if (xt4 == 0) {
                                        nodes0.insert(cnt4);
                                    }
                                    cnt4++;
                                }
                            } else {
                                int id4 = cntmap4[hand];
                                roadmap4[id4][j] = cnt3;
                                roadmap3[cnt3][j] = id4;
                            }
                            hand[j]--;
                        }
                        cnt3++;
                    }
                } else {
                    int id3 = cntmap3[hand];
                    roadmap3[id3][i] = current;
                    roadmap4[current][i] = id3;
                }
                hand[i]++;
            }
        }
    }

    printf("initxt:%d cur:%d cnt3:%d cnt4:%d zero:%d\n",init_xt, current, cnt3, cnt4,nodes0.size());
    auto val3 = new double[cnt3][18][34];
    memset(val3, 0, 18 * 34 * cnt3 * sizeof(double));
    double (*val4)[18] = new double[current][18];
    memset(val4, 0, 18 * current * sizeof(double));
    double (*val3t)[18] = new double[cnt3][18];
    memset(val3t, 0, 18 * cnt3 * sizeof(double));

    std::multimap<double, int, std::greater<>> queue;
//    printf("zero:%d\n",nodes0.size());
    for (auto id4 : nodes0) {
        queue.emplace(std::make_pair(MaxVal, id4));
        if(id4 < current) {
            for (int i = 0; i < 18; ++i) { val4[id4][i] = round_prob[i]; }
        }
    }
    //for zero nodes outside current
    for (int i = 0; i < 18; ++i) { val4[0][i] = round_prob[i]; }

    double minq = 20, minq2 = 16;
    while (!queue.empty()){
        auto top = queue.begin();
        if(top->second >= current) assert(nodes0.count(top->second) > 0);
        bool dflag = (minq < 0.014 && queue.size() == 28704);
        dflag = false;
        if(dflag) printf("st:%lf %d\n",top->first,top->second);
        assert(minq >= top->first);
        if(minq > top->first){
            minq = top->first;
            if(false) {
                printf("minq:%lf qu:%d ",minq,queue.size());
                int bestc = 0;
                double bestval = 0;
                int k3 = 1;
                int oldbest = -1;
                for (int j = 0; j < 2; ++j) {
                    bestval = 0;
                    for (int k1 = 0; k1 < 34; ++k1) {
                        if (k1 == oldbest) continue;
                        if (hand_cnt[k1] > 0) {
                            double val = 0;
                            for (int i = 0; i < 18; ++i) {
                                val += val3t[k3][i] * round_prob[i];
                            }
                            if (val > bestval) {
                                bestval = val;
                                bestc = k1;
                            }
                            ++k3;
                        }
                    }
                    printf("b:%s %lf\t", mname[bestc], bestval);
                    oldbest = bestc;
                }
                printf("\n");
                minq2 *= 0.8;
            }
        }
        assert(top->second > 0 && top->second < BIG);
        auto roads = roadmap4[top->second];
        for (int i = 0; i < 34; ++i) {
            if(dflag) printf("i:%d\n",i);
            int id3 = roads[i];
            assert(id3 >= 0 && id3 < BIG);
            if(id3 > 0){                        //top->second:14 --i--> id3:13
                if(dflag) printf("id3:%d\n",id3);
                int improve = -1;
                if((id3 == 2 || id3 == 4) && i == 12){
               //     printf("--id3:%d top:%lf %d\n",id3,top->first,top->second);
                }
                auto val4v = (top->second >= current ? val4[0] : val4[top->second]);
                for (int k = 0; k < 18 - 1; ++k) {
                    double newval = val4v[k + 1];
                    if((id3 == 2 || id3 == 4)){
                      //  printf("---id3:%d top:%lf %d k:%d i:%s val:%lf - %lf sval:%lf\n",id3,top->first,top->second,k,mname[i],val3t[id3][k],newval,val3[id3][k][i]);
                    }
                    if(val3t[id3][k] < newval){
                        assert(val3[id3][k][i] <= newval);
                        if(val3[id3][k][i] < newval) {
                            if(improve == -1) {
                                improve = k;
                                if(id3 == 2 || id3 == 4){
                             //       printf("id3:%d top:%lf %d k:%d i:%s val:%lf - %lf sval:%lf\n",id3,top->first,top->second,k,mname[i],val3t[id3][k],newval,val3[id3][k][i]);
                                }
                            }
                            val3[id3][k][i] = newval;
                        }
                    }
                }
                if(improve >= 0) { //top->second:14 --i--> id3:13 --j-->id4:14
                    //calculate val3t 0-18
                    for (int k = 0; k < 18; ++k) { //arrive@k total value (val3t[k])
                        if(dflag) printf("improve k:%d\n",k);
                        double tval = 0;
                        double stval = 1;

                        for (int l = k; l < 18; ++l) { //leave@l value
                            double dstval = 1;
                            for (int n = 0; n < 34; ++n) {
                                if (val3[id3][l][n] > 0) {
                                    tval += stval * known_remain_cnt[n] / remain_sum * val3[id3][l][n];
                                    dstval -= known_remain_cnt[n] / remain_sum;
                                }
                            }
                            stval *= dstval;
                        }
                        assert(tval >= 0 && tval < 1);
                        assert(tval >= 0 && tval < round_prob[k]);
                        assert (val3t[id3][k] <= tval);
                        val3t[id3][k] = tval;
                        if(dflag) printf("improvefin k:%d\n",k);
                    }

                    //send to all road4
                    auto roads3 = roadmap3[id3];
                    for (int j = 0; j < 34; ++j) {
                        int id4 = roads3[j];
                        if(dflag) printf("id4:%d\n",id4);
                        assert(id4 >= 0 && id4 < BIG);
                        if(id4 < current) {
                            if (id4 == top->second) {
                                for (int k = 0; k < 18; ++k) {
                                    assert(val4[id4][k] > val3t[id3][k]);
                                }
                            }
                            if (id4 > 0 && id4 != top->second) {
                                bool improve2 = false;
                                double oldval = 0;
                                for (int k = 0; k < 18; ++k) {
                                    oldval += val4[id4][k] * round_prob[k];
                                }

                                for (int k = 0; k < 18; ++k) {
                                    if (val4[id4][k] < val3t[id3][k]) {
                                        val4[id4][k] = val3t[id3][k];
                                        improve2 = true;
                                    }
                                }
                                if (improve2) {
                                    if (dflag) printf("id4 improve2:%d\n", id4);
                                    assert(id4 != top->second);
                                    for (auto test = queue.lower_bound(oldval);
                                         test != queue.upper_bound(oldval); ++test) {
                                        if (dflag) printf("eraze:%lf %d\n", test->first, test->second);
                                        if (test->second == id4) {
                                            queue.erase(test);
                                            break;
                                        }
                                    }
                                    double val = 0;
                                    for (int k = 0; k < 18; ++k) {
                                        val += val4[id4][k] * round_prob[k];

                                    }
                                    assert(val < MaxVal);
                                    if (dflag) printf("fin\n");

                                    queue.emplace(std::make_pair(val, id4));
                                }
                            }
                        }
                    }
                }
            }
        }
        assert(queue.count(top) > 0);
        int erasenum = 0;
        for (auto test = queue.lower_bound(top->first); test != queue.upper_bound(top->first); ++test) {
            if(dflag) printf("eraze2:%lf %d\n",test->first,test->second);
            if (test->second == top->second) {
                queue.erase(test);
                erasenum++;
                break;
            }
        }
        if(dflag)printf("enum:%d\n",erasenum);
        assert(erasenum==1);
    }
    int k3 = 1;
    bool eflag = false;
    int bestc = 0; double bestval = 0;
    for (int k1 = 0; k1 < 34; ++k1) {
        if(hand_cnt[k1] > 0){
            printf("%s ",mname[k1]);
            double val = 0;
            for (int i = 0; i < 18; ++i) {
                printf("%lf ", val3t[k3][i]);
                val += val3t[k3][i] * round_prob[i];
            }
            printf("\n");
            if(val>bestval) {
                bestval = val;
                bestc = k1;
                eflag = false;
            } else if(val == bestval)
                eflag = true;
            ++k3;
        }
    }
    if(eflag)printf("not separated!\n");
    return (eflag ? -bestc : bestc);
}

