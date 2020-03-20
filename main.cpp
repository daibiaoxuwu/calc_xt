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

    for (int xt = init_xt; xt > 1; --xt) {
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
                                if (xt2 < xt) {//TODO <=
                                    if (nodes[xt2].count(hand) == 0) {
                                        cntmap[hand_cnt] = cnt;
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

    auto valmap = new std::vector<std::vector<double>*>*[cnt];
    memset(valmap,0,cnt*sizeof(std::vector<std::vector<double>*>*));
    //valmap: vectors of:
    // firstone: calculated val0 val1 val2 val1 val2...
    //  (number0) 10% -> hand A : val0 val1 val2 val1 val2...
    //  (number0)  5% -> hand B : val0 val1 val2 val1 val2...
    //  (number0)  3% -> hand C : val0 val1 val2 val1 val2...
    //val0: min hu time
    //for each newhand A B C:
    //      hurate@round (round=1,2,3...) = sum ( val1 * val2 ^ (round - val0) )
    //      eg. val0 = 0:
    //          hurate@round 1 = sum ( val1 * val2 )
    //          hurate@round 2 = sum ( val1 * val2 ^ 2)
    //          hurate@round 3 = sum ( val1 * val2 ^ 3)
    //      hurate before round: = sum ( val1 * val2 * (1 - val2 ^ round) / (1 - val2)
    //for this hand:
    //hurate:       ab      ab2     ab3
    //transrate:    cd      cd2     cd3
    //c:trate/d
    //d:stayrate
    //my hurate:
    //      (abcd/(b-d))*b^k    -     (abcd/(b-d))*d^k



    auto dvals = new double[cnt];
    memset(dvals, 0, cnt*sizeof(double));
    std::priority_queue<std::pair<double, int>> queue;
    const int DECIDE_ROUND = 10.0;

    for (auto hand : nodes[1]) {
        int ting_cnt = 0;
        for (int i = 0; i < 34; ++i) {
            hand[i]++;
            if (calc_xt(hand) == 0) ting_cnt += known_remain_cnt[i]; //TODO: known_remain_cnt
            hand[i]--;
        }
        double val = ting_cnt / (double)remain_sum;
        int roadcnt = cntmap[hand];
        valmap[roadcnt] = new std::vector<std::vector<double>*>({new std::vector<double>({0.0, val/(1-val), 1 - val})});
        //k round hu: sum ( val * val2 ^ (k - val0) )
        double dval = 1 - pow(1 - val, DECIDE_ROUND); //DE_R = 1: dval = val
        dvals[roadcnt] = dval;
        queue.emplace(std::make_pair(dval, roadcnt));
    }
    while (!queue.empty()) {
        auto top = queue.top();
        for (auto i : roadmap[top.second]) {
            if (dvals[i.first] < top.first) {
                //calculate new dval
                double tval = known_remain_cnt[i.second] / (double) remain_sum;
                std::vector<std::vector<double> *> *thisval = valmap[i.first];
                if(thisval == nullptr) thisval = new std::vector<std::vector<double> *>();
                double stayrate = 1;
                for (size_t k = 1; k < thisval->size(); ++k) { //skip first one
                    stayrate -= thisval->at(k)->at(0);
                }
                //c: tval / stayrate
                //d: stayrate
                auto val0 = thisval->at(0);
                for (size_t k = 1; k < thisval->size(); ++k) { //skip first one
                    auto vals = thisval->at(k);
                    for (int j = 0; j < (vals->size() - 2) / 2; ++j) {
                        //a: vals->at(j)
                        //b: vals->at(j+1)




                    }
                }
            }
        }
    }

    return 0;

}
