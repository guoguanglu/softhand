# Softhand
This is my note on Andrew-Ng's machining learning. Thank you for asking questions.

***
![](/fig/log.png)  
- Author: Guo Guanglu  
- E-mail: 2360889142@qq.com
- QQ: 2360889142  

***
[**Back to github.io**][github.io]

***
## Content  
* [Introduction](#introduction)  
* [Targets](#targets)  
* [Design](#design)  
* [Conclusion](#conclusion)   

***   
Introduction   
---  
Due to rigid materials, there are some problems, such as hard, non-scalable, etc. The softhand project uses flexible materials to achieve the simulation of the opponent, and adds some additional functions, for example visual recognition of handwritten numberals, flexible hand to make the corresponding gestures.The related review can be referred to :[Flexible Robot References][Flexible robot references]   


***
Targets   
---  
In the project, we mainly achieve the following goals:  
1. Realize manual control of flexible gripper  
2. Realize the control of the upper computer to the flexible gripper  
3. Realize manually the digital display of the number 1 to 5 in the upper comuter  
4. Realize flexible grippers to grasp different objects  
5. Realize visual recognition of handwritten digits, flexible hands showing corresponding gestures   


***  
Design   
---  
The softhand project is mainly divided into four parts:  
1. Making flexible hand body  
2. Hardware circuit design  
3. The host computer interface preparation  
4. Handwritten digit recognition  

### Making flexible hand body   
We adopt the air-actuated method. The subject material of the actuator is made of silicone and disigned usign PN(PneuNets) structure.  
![](/fig/PN.png)  
Then we use Abaqus software to perform FEM analysis on PneuNet actuators. FEM allows us to model the actuator and see how to change various parameters.  
![](/fig/FEM.png)  
The PneuNets actuator consists of two main parts: the main body and the bottom layer. The body includes an actuating chamber and the bottom layer includes a strain limited material. The two parts wer molded separately and glued together, where the 3D printing technology was used to make the mold. Here is the entire production process.  
![](/fig/process.png)   
The result is as follows:  
![](/fig/handbody.png)   

### Hardware circuit design  
The block diagram of the entire control system is shown below. we use stm32 as controller, the solenoid valve as the actuation switch, 6V air pump as actuation source, the grasper acts as the controlled body, and the gyroscope to  perform the automatic control of the attitude.  
![](/fig/sch.png)  
Specific related designs can be viewed [Flexible Robot References][Flexible robot references]. The final circuit is as follows:  
![](/fig/circuit.png)  

### The upper computer interface preparation  

The upper computer interface is written by Qt software and the effect is shown in the below figure.  
![](/fig/interface.png)  

###  Handwritten digit recognition  
Due to the work that is was done by another person in our group, the data has not been organized ,so write it skip ^-^  

***  
Conclusion  
---  
Through this project, I have improved the purchase of hardware materials, the circuit design, the pracitcal ability has been strengthened, and I have learned and studied the use of software such as soliworks, keil5 and qt5 etc. The important goal is to make me have a deep understanding of the complete project. Here I thank my team!^-^  








[github.io]:https://guoguanglu.github.io "guoguanglu github.io"  
[Flexible robot references]:https://github.com/guoguanglu/softhand/tree/master/related%20information
