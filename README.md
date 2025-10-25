# line-following-bot-PID

## WHAT I DID

**In first part** {where we define variable,constants,..} i defined 


1.Pins{sensor pins and motor driver pins}


2.Defined tuning parameters and variables req for PID Controller


3.Defined base speed for motors with which they will rotate in normal codition.
<br> <br> <br> 

**In Setup part** {Simply did three things}




1.set sensor pins as input pins


2.set motor driver pins as output pins



3.setup serial monitor to pop up a starting msg so as to confirm it has started.  
<br> <br> <br> 


**IN Void loop part**



In this part took reading from all five sensors and acc to ten possible cases returned



 an error value  


then calculated pid terms i.e integral,derivative and correction term and did integral


 windup





then in controlMotor part calculated speed for both side motors and then set IN1,IN2


IN3,IN4,ENA,ENB accordingly


<br> <br> <br> 

**In summary**
<br>
take reading --> calculate error --> get correction term using pid controller-->adjust speeds
<br> <br> <br> <br>


## WHAT DID I LEARNED FROM THIS ?
In this line following bot i have to use PID controller and motor driver  <br>
along with simply taking input from sensor and using if else statements <br>
APART FROM any other part of this bot , PID controller was the best part that i got to <br>
know i was amazed after knewing how it was developed from only proportional controller to PI controller <br>
then finally to PID controller <br>
although i  write code for motor driver {L298N} but didnt studied much about it <br>
but i will do so in some time i just know how to write code and what is the use of each line that i have <br>
used in the code <br>


## HOW I DID SO ?
i have taken help of gemini in writting ths code but for only PID controller and motor driver <br> 
rest part is  done by myself


## WHAT CAN BE DONE BETTER
i think the way i used to calculate error can be improved rather than writting so many if else statements <br>


