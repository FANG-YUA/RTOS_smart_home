2025.8.16 周六  顶层设计1

实现顶层与采集模块和控制模块的信号量通信
问题1:顶层与采集模块和控制模块的信号量通信时，ack与req的收发代码有高重复性。
解决：建立了“mmc”存放模块之间通信的代码。
     结构体里包括：采集与顶层通信的信号量ack,req,共享数组以及数值长度；控制与顶层通信的信号量ack,req,共
     数组以及数值长度。目前实现了结构体的构建以及初始化。

2025.8.18 周一  顶层设计2

步骤：建立mmc.c/.h，包括mmc_ctrl_require和mmc_ctrl_init。对于风扇与灯光的控制，使用宏定义代替01。以及判断开
关的气温/亮度阈值，也使用宏定义，优点在于方便后续修改。建立business_test.c/.h文件，使用mock_sample_task_entry
和mock_switch_task_entry，返回气温/亮度定值，以及风扇与灯光的打开，以此实现假采集，测试顶层设计的可用性，每一步
都可以打印语句，判断运行情况，方便错误调试。测试现在使用的是定值，后续可以实现手动修改值和自动修改值进行测试。

2025.8.20 周三  温度采集驱动的实现

目的：实现ADC采集电压和计算NTC的电阻值。
步骤：使用cubemx配置ADC端口，移植至自己的项目中的时候，需要把adc相关的.c.h文件一并添加，同时，在stm32f1xx_hal_cont.h文
件里把“#define HAL_ADC_MODULE_ENABLED   */”取消注释，不然会出现ADC 函数未编译的链接阶段错误（L6218E）。

2025.8.21 周四  xshell调试

下载了xshell,学会使用xshell连接串口，调试时代码卡在NTC_Init();中，步进显示READ_BIT(hadc->Instance->CR2, ~(ADC_CR2_ADON
| ADC_CR2_DMA | ADC_CR2_SWSTART| ADC_CR2_JSWSTART | ADC_CR2_JEXTTRIG | ADC_CR2_JEXTSEL | ADC_CR2_TSVREFE)) == tmp_cr2 
这个条件为假。意味着 ADC 控制寄存器（CR2）的状态不符合预期，可能是 ADC 处于异常状态或配置存在问题。检查可能是stm32f1xx_hal_gpio_ex.c
和stm32f1xx_hal_msp.c出现问题，应该还是使用cubemx配置的时候没有移植完全。已解决。




