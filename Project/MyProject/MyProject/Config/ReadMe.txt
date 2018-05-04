@brief : A category (i.e. Game) must be supplied for the Config specifier. This determines which configuration files the class's variables are read from and saved to. All possible categories are defined in FConfigCache.ini. For a list of all configuration file categories, see Configuration Categories . 
@ref : https://docs.unrealengine.com/latest/INT/Programming/Basics/ConfigurationFiles/index.html


==============
其它涉及事项：
https://blog.csdn.net/wzqnn/article/details/73649502
设置最大和最小帧率

可以在 BaseEngine.ini 文件中设置来控制这个变量，默认如下：

[/Script/Engine.Engine]bSmoothFrameRate=true MinSmoothedFrameRate=22

MaxSmoothedFrameRate=62