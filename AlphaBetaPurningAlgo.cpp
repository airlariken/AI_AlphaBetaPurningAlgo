//
//  AlphaBetaPurningAlgo.cpp
//  Ai_AlphaBetaPruning(井字棋)
//
//  Created by 陈梓玮 on 2021/4/24.
//

#include "AlphaBetaPurningAlgo.hpp"


vector<int> AlphaBetaPurningAlgo::mainAlgoFun(vector<int>chessboard)
{
//    vector<bool> is_ouccpied(9,0);//初始化不可下棋子位置全为0
//    vector<int>chessboard(9, 0);//初始化棋盘全为-1
//    vector<int>chessboard{1,-1,-1,-1,-1,0,0,1,1};
//    vector<int>chessboard{1,1,-1,-1,1,-1,0,-1,0};
//    vector<int>chessboard{1,-1,1,1,-1,0,-1,0,0};
    
    int tga = is_win(chessboard);
    if (tga == 1){
        cout<<"电脑赢了"<<endl;
        return vector<int>();
    }
    if (tga == -1){
        cout<<"人赢了"<<endl;
        return vector<int>();
    }
    //游戏没结束
    int next_step = -1, best_point = INT_MIN;
    AlphaAndBeta temp;
    for (int i = 0; i < 9; ++i) {
        if (chessboard[i] == 0) {
            chessboard[i] = 1;//电脑下，电脑为MAX
            AlphaAndBeta tt = subFun(chessboard, AlphaAndBeta(INT_MIN, INT_MAX), -1);
                temp.alpha =  max(tt.alpha, max(temp.alpha, tt.beta));
//            cout<<"下第"<<i<<"个位置的评价函数为"<<temp.alpha<<endl;
            if (temp.alpha > best_point) {
                best_point = temp.alpha;
                next_step = i;
            }
            chessboard[i] = 0;//回溯
        }
        
    }
    if (next_step == -1) {
        return chessboard;
    }
    chessboard[next_step] = 1;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout<<chessboard[i*3+j]<<'\t';
        }
        cout<<endl;
    }
    return chessboard;
}
AlphaAndBeta AlphaBetaPurningAlgo::subFun(vector<int>chessboard, AlphaAndBeta parent,int max_or_min)//max为1 min -1
{
    int tga = is_win(chessboard);
    if (tga == 1 && max_or_min == -1)
        return AlphaAndBeta(INT_MIN, 1);
    else if (tga == 1 && max_or_min == 1)
        return AlphaAndBeta(1, INT_MAX);
    else if (tga == -1 && max_or_min == -1)
        return AlphaAndBeta(INT_MIN, -1);
    else if (tga == -1 && max_or_min == 1)
        return AlphaAndBeta(-1, INT_MAX);
    //游戏没结束
    AlphaAndBeta temp;
    for (int i = 0; i < 9; ++i) {
        if (chessboard[i] == 0) {
            chessboard[i] = max_or_min;
            //判断是否胜利
            tga = is_win(chessboard);
            if (tga == 1 && max_or_min == -1)
                return AlphaAndBeta(INT_MIN, 1);
            else if (tga == 1 && max_or_min == 1)
                return AlphaAndBeta(1, INT_MAX);
            else if (tga == -1 && max_or_min == -1)
                return AlphaAndBeta(INT_MIN, -1);
            else if (tga == -1 && max_or_min == 1)
                return AlphaAndBeta(-1, INT_MAX);
            
            //判断是否平局
            bool is_even = 1;
            for(int i = 0; i < 9 ;++i)
            {
                if (chessboard[i] == 0) {
                    is_even = 0;
                    break;
                }
            }
            if (is_even) {
                if (max_or_min == 1) //游戏结束
                    return AlphaAndBeta(0,INT_MAX);
                if (max_or_min == -1) //意味着上一层是
                    return AlphaAndBeta(INT_MIN,0);
            }
            
            AlphaAndBeta tt = subFun( chessboard, parent, max_or_min*-1);
            if (max_or_min == 1)
                temp.alpha = max(parent.alpha, max(tt.alpha, max(temp.alpha, tt.beta)));
            else if(max_or_min == -1)
                temp.beta = min(parent.beta, min(tt.beta, min(temp.beta, tt.alpha)));
            chessboard[i] = 0;//回溯
        }
        if (temp.alpha >= temp.beta)
            return temp;//剪枝！！！！
    }
    return temp;
}
int AlphaBetaPurningAlgo::is_win(const vector<int> &chessboard)//1下赢返回1， -1下赢返回-1
{
    bool left_win_flag = 0, right_win_flag = 0;
    for (int i = 0; i < 3; ++i) {       //判断横着直线是否赢了
        left_win_flag = 0;   right_win_flag = 0;
        for (int j = 0; j < 3; ++j) {
            if (chessboard[i*3+j] == 1 && right_win_flag == 0)
                left_win_flag = 1;
            else if (chessboard[i*3+j] == -1 && left_win_flag == 0)
                right_win_flag = 1;
            else{
                left_win_flag = 0;
                right_win_flag = 0;
                break;
            }
        }
//        if (left_win_flag == 0 && right_win_flag == 0)
//            break;
        if(left_win_flag == 1) return 1;
        else if(right_win_flag == 1) return -1;
        
    }
    
    
    for (int i = 0; i < 3; ++i) {       //判断横着直线是否赢了
        left_win_flag = 0;   right_win_flag = 0;
        for (int j = 0; j < 3; ++j) {
            if (chessboard[i+3*j] == 1 && right_win_flag == 0)
                left_win_flag = 1;
            else if (chessboard[i+3*j] == -1 && left_win_flag == 0)
                right_win_flag = 1;
            else{
                left_win_flag = 0;
                right_win_flag = 0;
                break;
            }
        }
//        if (left_win_flag == 0 && right_win_flag == 0)
//            break;
        if(left_win_flag == 1) return 1;
        else if(right_win_flag == 1) return -1;
    }
    
    if (chessboard[0] == 1 && chessboard[4] ==1 && chessboard[8] == 1)
        return 1;
    else if (chessboard[0] == -1 && chessboard[4] == -1 && chessboard[8] == -1)
        return -1;
    else if (chessboard[2] == 1 && chessboard[4] == 1 && chessboard[6] == 1)
        return 1;
    else if (chessboard[2] == -1 && chessboard[4] == -1 && chessboard[6] == -1)
        return -1;
    return 0;
}

//int AlphaBetaPurningAlgo::fx(vector<int>chessboard, int max_or_min)//评价函数
//{
//
//    return 0;
//}

void AlphaBetaPurningAlgo::gameStart()
{
    char code = '#';
    vector<int>my_chessboard(9,0);
    cout<<"1.人先手    2.电脑先手"<<endl;
    cin>>code;
    if (code == '1') {
        while (1) {
            int my_step;    cin>>my_step;
            my_chessboard[my_step] = -1;
            if(is_win(my_chessboard) == -1)   {cout<<"人赢了"<<endl;return;}
            my_chessboard = mainAlgoFun(my_chessboard);
            if(is_win(my_chessboard) == 1)   {cout<<"电脑赢了"<<endl;return;}
        }
    }
    else if(code == '2'){
        while (1) {
            my_chessboard = mainAlgoFun(my_chessboard);
            if(is_win(my_chessboard) == 1)   {cout<<"电脑赢了"<<endl;return;}
            int my_step;    cin>>my_step;
            my_chessboard[my_step] = -1;
            if(is_win(my_chessboard) == -1)   {cout<<"人赢了"<<endl;return;}
        }
    }
}
void AlphaBetaPurningAlgo::QT_clear()
{
    chessboard.clear();
    chessboard.resize(9, 0);
}
int AlphaBetaPurningAlgo::QT_gameStart(bool &win)
{
    vector<int> temp_chessboard = chessboard;
    if(is_win(chessboard) == -1)   {cout<<"人赢了"<<endl;win = 1;return INT_MIN;}
    bool is_even = 1;
    for (int i = 0; i < chessboard.size(); ++i) {
        if (chessboard[i] == 0) {
            is_even = 0;
            break;
        }
    }
    if (is_even)
        return -2;
    chessboard = mainAlgoFun(chessboard);
    if(is_win(chessboard) == 1)   {cout<<"电脑赢了"<<endl;win = 1;}
    for (int i = 0; i < chessboard.size(); ++i) {
        if (temp_chessboard[i] != chessboard[i]) {
            return i;//找到机器下的这一步;
        }
    }
        
    return -2;//错误返回
}
