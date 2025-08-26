#ifndef CONFIG_H
#define CONFIG_H

/*场景及玩家设置*/
#define playscene_Width 1280 //游戏场景宽度
#define playscene_Height 720 //游戏场景高度
#define playscene_Background1 ":/new/pixmap/background.jpg" //游戏场景背景图
#define playscene_Title "大鱼吃小鱼" //游戏场景标题
#define Icon0 ":/new/pixmap/player1.png" //游戏场景图标
#define Icon1 ":/new/pixmap/icon1.png" //开始界面图标
#define player_Pix1 ":/new/pixmap/player1.png" //玩家1左向图
#define player_Pix1_ ":/new/pixmap/player1_.png" //玩家1右向图
#define player_Pix2 ":/new/pixmap/player1.png" //玩家2左向图
#define player_Pix2_ ":/new/pixmap/player1_.png" //玩家2右向图
#define player_Width 35 //玩家初始宽度
#define player_Height 35 //玩家初始高度
#define player_Speed 3 //玩家速度

/*数据设置*/
#define fish_Speed 2 //鱼速度
#define maxnum_fish 10 //鱼的最大数目
#define fish_recordor 3000 //产生鱼的间隔
#define per_turn 5 //分数转化率倒数

/*鱼的图片*/
#define fish_Lv1_Pix ":/new/pixmap/fish_lv1.png"   //lv1鱼向左图
#define fish_Lv1_Pix_ ":/new/pixmap/fish_lv1_.png" //lv1鱼向右图
#define fish_Lv2_Pix ":/new/pixmap/fish_lv2.png"   //lv2鱼向左图
#define fish_Lv2_Pix_ ":/new/pixmap/fish_lv2_.png" //lv2鱼向右图
#define fish_Lv3_Pix ":/new/pixmap/fish_lv3.png"   //lv3鱼向左图
#define fish_Lv3_Pix_ ":/new/pixmap/fish_lv3_.png" //lv3鱼向右图
#define fish_Lv4_Pix ":/new/pixmap/fish_lv4.png"   //lv4鱼向左图
#define fish_Lv4_Pix_ ":/new/pixmap/fish_lv4_.png" //lv4鱼向右图
#define fish_Lv5_Pix ":/new/pixmap/fish_lv5.png"   //lv5鱼向左图
#define fish_Lv5_Pix_ ":/new/pixmap/fish_lv5_.png" //lv5鱼向右图
#define fish_Lv6_Pix ":/new/pixmap/fish_lv6.png"   //lv6鱼向左图
#define fish_Lv6_Pix_ ":/new/pixmap/fish_lv6_.png" //lv6鱼向右图
#define fish_Lv7_Pix ":/new/pixmap/fish_lv7.png"   //lv7鱼向左图
#define fish_Lv7_Pix_ ":/new/pixmap/fish_lv7_.png" //lv7鱼向右图
#define fish_Lv8_Pix ":/new/pixmap/fish_lv8.png"   //lv8鱼向左图
#define fish_Lv8_Pix_ ":/new/pixmap/fish_lv8_.png" //lv8鱼向右图

/*背景音乐及音效*/
#define bg_music1 ":/new/music/bg_music1.wav" //背景音乐1
#define bg_music2 ":/new/music/bg_music2.wav" //背景音乐2
#define player_getscore1 ":/new/music/player_getscore1.wav" //得分音效1
#define player_getscore2 ":/new/music/player_getscore2.wav" //得分音效2
#define player_loselife ":/new/music/player_loselife.wav" //扣血音效

#endif // CONFIG_H
