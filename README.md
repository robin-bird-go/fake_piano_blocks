# fake_piano_blocks
钢琴块的低仿拉胯版

# 首先是食用指南

## 1、easy_x软件准备

> > 双击该安装程序，并在你的vs上（显示是Visual C++ 版本号）安装，直接点击就送
> >
> > ![image-20220118142031590](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220118142031590.png)
> >
> > 或者移步官网，下载最新版
> >
> > https://easyx.cn/

## 2、打开.sln项目文件

> > ![image-20220119215124319](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220119215124319.png)
> >
> > ![image-20220119215133129](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220119215133129.png)
> >
> > 进行一些基础的设置
> >
> > 1、对项目右键，选择属性
> >
> > ![image-20220118144101982](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220118144101982.png)
> >
> > 2、在**C/C++**选项中找到SDL检查，关闭
> >
> > ![image-20220118144227015](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220118144227015.png)
> >
> > 3、切换到**高级**，改变字符集为“多字节字符集”
> >
> > ![image-20220118144348629](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220118144348629.png)
> >
> > 最后点击右下角“应用”即可

## 3、直接跑main.c程序

> > ![image-20220119215434162](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220119215434162.png)
> >
> > ![image-20220119215456368](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220119215456368.png)
> >
> > 有几个自己发现的不足之处，如果觉得很接受不了的或者有其他认为需要改进的地方，请提出宝贵建议,thxx
> >
> > ```PYTHON
> > #1、有bgm的版本，用beep函数播放背景音乐占用的CPU主进程导致一播放声音就会卡，自己不太会用多线程操作
> > #2、存本地游戏记录只有1页，超过了就会出大问题，正在考虑限制记录数（现已支持
> > #3、双向版本好像右侧往上的方块判定比较慢？暂时没发现问题所在（原来判定条件整错了2333，已解决
> > ```

## 4、~游玩注意~十分重要~ヽ(`Д´)ﾉ

> > 内测的同学说游戏规则不太醒目，所以在这里再简明说一下操作方法
> >
> > （1）菜单界面：用"w"和“s”键来上下选择切换，回车键选中
> >
> > （2）设置那里，当光标指示到某一行时，如果想修改值，先回车，等待下方提示弹出后，直接用键盘输入数字，它会自己显示值的改变，之后再回车保存结果√
> >
> > ![image-20220119215858493](C:\Users\robinbird\AppData\Roaming\Typora\typora-user-images\image-20220119215858493.png)
> >
> > （3）游戏的打击键是按键盘实现的，1-6键顺序是asdfgh，（键盘第二行左边开始）
> >
> > （4）游戏中途可以暂停，按下空格键就行，如果想退出，就**再**按下esc，等界面显示press_blank_space_to_return这里，再按下空格键，即可退出；不想退出就再按一次空格键
> >
> > OVER,祝游戏体验愉快(^_−)☆



作者：一只小知更鸟

qq:1197737573

欢迎大家来私戳我反馈，宝贵的意见是对俺最大的支持！
