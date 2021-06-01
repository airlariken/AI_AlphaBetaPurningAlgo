//
//  AlphaBetaPurningAlgo.hpp
//  Ai_AlphaBetaPruning(井字棋)
//
//  Created by 陈梓玮 on 2021/4/24.
//

#ifndef AlphaBetaPurningAlgo_hpp
#define AlphaBetaPurningAlgo_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
//#define WINSCORE +1000
//#define LOSESOCRE -1000
using namespace std;


struct AlphaAndBeta
{
    int alpha = INT_MIN;
    int beta = INT_MAX;
    AlphaAndBeta(int a, int b):alpha(a), beta(b){}
    AlphaAndBeta() = default;
};

class AlphaBetaPurningAlgo
{
//    vector<vector<int>>chessboard;
    
public:
//    AlphaBetaPurningAlgo():chessboard(3){
//        for (int i = 0; i < chessboard.size(); ++i)
//            chessboard[i].resize(3, -1);
//        }
    vector<int> mainAlgoFun(vector<int>chessboard);
    AlphaAndBeta subFun(vector<int>chessboard, AlphaAndBeta parent, int max_or_min);
    int is_win(const vector<int> &chessboard);//-1或1赢了，0是游戏没结束
    void gameStart();//命令行开始
//    int fx(vector<int>chessboard, int max_or_min);//评价函数
    int QT_gameStart(bool &win);
    void QT_clear();
    vector<int>chessboard;//qt接口
};
#endif /* AlphaBetaPurningAlgo_hpp */
