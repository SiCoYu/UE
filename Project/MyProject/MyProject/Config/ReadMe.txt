@brief : A category (i.e. Game) must be supplied for the Config specifier. This determines which configuration files the class's variables are read from and saved to. All possible categories are defined in FConfigCache.ini. For a list of all configuration file categories, see Configuration Categories . 
@ref : https://docs.unrealengine.com/latest/INT/Programming/Basics/ConfigurationFiles/index.html


==============
Unreal Engine 4 减少编辑器的帧率
https://www.cnblogs.com/cynchanpin/p/6698855.html

默认的，打开UE4的编辑器，显卡会以全速渲染场景，在我的机器上。是120FPS。
整个机器就開始轰鸣了。资源占用太凶了。事实上全然不是必需这样，帧率在60左右就足够了。
那怎么改动呢，试了非常多办法。最有效的是改动BaseEngine.ini配置文件。改动以下一行：
SmoothedFrameRateRange=(LowerBound=(Type="ERangeBoundTypes::Inclusive",Value=5),UpperBound=(Type="ERangeBoundTypes::Inclusive",Value=50))

把最后的Value的值。改成你想要的值，我改成50。重新启动编辑器。风扇最终清静了。
最后说下，怎样看帧率，有两种办法：
一种是改动编辑器偏好设置->Show Frame Rate and Memory，这样的方法的优点是。是全局的，重新启动后，编辑器会记住。
一种是在控制台命令中。输入stat fps，这样会在游戏界面上显示当前的fps。这个编辑器重新启动后。须要又一次开启。

==============
首先这里 Project 里面设置
MyProject\Config\DefaultEngine.ini
[/Script/UnrealEd.EditorEngine]
SmoothedFrameRateRange=(LowerBound=(Type="ERangeBoundTypes::Inclusive",Value=5),UpperBound=(Type="ERangeBoundTypes::Inclusive",Value=24))

然后引擎 BaseEngine.ini 里面设置
SmoothedFrameRateRange=(LowerBound=(Type="ERangeBoundTypes::Inclusive",Value=5),UpperBound=(Type="ERangeBoundTypes::Inclusive",Value=50))













