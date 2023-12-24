Elevator Simulator

Elevator Simulator Design
-------------------------

### Introduction

This paper describes the design and development of a system that simulates the operation of an elevator model. The objects required to build the model will be identified, and a system will be developed that simulates the model. Each of the objects will act independently and manage its own data. One or more objects will manage the user interface. The model allows the user to specify how many of the principal objects the simulation should include on a given run. The output of the model will be a report showing the activity of the major objects.

### The Model

#### Description

Elevator simulators come in a variety of shapes and forms. They typically simulate passenger flow, but have also simulated only elevator movement. The passenger flow simulators typically perform one or a combination of three scenarios:

1.  Passenger flow from the lobby to the upper floors.
2.  Passenger flow from upper floors to the lobby.
3.  Passenger flow between floors.

For our model to simulate an elevator and provide meaningful information, the output will determine, for a given number of elevators, how many passengers per hour that it can carry from the lobby to the upper floors of the building.

The number of elevators in the building will be determined by the user. The building will contain a fixed number of floors. The number of passengers that can fit into the elevator will be fixed. The passengers will be counted as they leave the elevator at their destination floor. The destination floor will be determined using a "random" Poisson interval. When all of the passengers in the elevator have reached their destination floors, the elevator will return to the lobby to pickup more passengers. The simulation will continue until the user cancels it via keystroke. A report will be generated showing the activity of the elevators and passengers.

#### Division into objects

The first step of identifying objects and classes began by generating a set of candidate classes and objects using the classical approach and behavior analysis. The eligible classes and objects generated using the classical approach are shown in Table 1. Abstractions that relate to system function points revealed during behavior analysis are shown in Table 2.

Tangible Things

Roles

Events

Interactions

Organizations

External Systems

building  
elevator  
buttons  
cable  
motor  
pulley  
motor controller  
hydraulic  
cylinder  
hydraulic pump  
hydraulic  
controller  
door edge  
closed and locked switch  
full open switch  
floor indicator  
bell / chime  
lights  
fan

rider  
repair person  
inspector  
observer

request to floor  
request floor  
door recycle  
door close  
door open  
go up  
go down  
stop  
ring bell  
update floor  
indication  
go to floor  
change  
directions  
break down

elevator and passengers  
floor and passengers  
elevator and floor

lift system  
door system  
building  
floors  
elevators  
passenger  
requests

power  
building  
closed circuit  
television  
emergency  
phone  
security

Table 1 - List of eligible objects discovered during analysis.

Behaviors

User input for the number of elevators in the building.  
User input to stop the simulation.  
A random number of passengers load from lobby onto the elevator and requests a floor.  
An observer counts the passengers as they load and limit them to the elevator capacity.  
The elevator closes it's doors after a predetermined amount of time after they are open.  
The passengers randomly request a floor number for where they want to go.  
The elevator determines the lowest floor request from all the passengers when traveling up from the lobby and travels to that floor.  
The passenger unloads at their requested floor.  
An observer counts the passengers as they unload from the floor.  
A random floor is selected for each passenger on the elevator.  
The elevator returns to the lobby for more passengers when all the passengers have departed to their requested floors.  
The observer reports the results to the user.

Table 2 - List of behaviors discovered during analysis.

After perusing the list of possible objects, the elevator is determined to be a primary object. The roles and responsibilities that this abstraction should encompass is then considered. The elevator is responsible for keeping track of which floor it is on, which direction it is traveling, the passengers on board, and the state of operation. Responsibilities such as direction, floor number, and state may seem like overkill for a simple lobby-to-floor elevator simulation; however, in anticipation of possible reuse or expansion, they are included.

These responsibilities are turned into services so that the user interface or other objects can acquire this information. These services provide the return of current information. Other services needed for the elevator include loading and unloading of passengers. The abstraction of the elevator class is summarized as follows:

Name:

Elevator

Responsibilities:

Keep track of the current floor position, the direction and state of operation, and the number of passengers aboard and their destination.

Operations:

load\_passengers  
unload\_passengers  
current\_passengers  
current\_floor  
current\_direction  
current\_state

Attributes:

passengers  
floor  
direction  
state  
elevator\_id

Instances of this class have a dynamic life cycle, which can be expressed in the state transition diagram shown in Figure 1. Here it can be seen that upon initialization, an instance of this class moves to the idle state, where it begins checking for passengers. The elevator will load the maximum passengers, and begin moving up to the lowest floor request. The elevator will then stop and unload the passenger(s). If there are more passengers to unload, the elevator will go to the moving up state. If there are no more passengers in the elevator, it will begin moving down until it reaches the lobby. When the elevator reaches the lobby, it will go to the load passengers state.

![[Elevator Life Cycle]](images/elev1.gif)  
Figure 1. Elevator life cycle.

The behavior of the elevator class is now specified in enough detail so that it can be used in scenarios with other clients that are discovered during analysis.

After looking at the elevator object, it is determined that the passenger portion may posses some complexity and would be a good candidate for a subclass. Its primary responsibility would be to keep track of the destination floor of the passenger. The abstraction of the passenger class is summarized as follows:

Name:

Passenger

Responsibilities:

Keep track of the destination floor.

Operations:

Current\_destination

Attributes:

Destination\_floor

One of the few requirements for the simulator is a user interface. A likely place to handle screen output and input would be from the observer point of view. An observer class could gather statistics from each elevator and display them on the screen, and process any operator requests. It would play the role of a SCADA (Supervisory Control and Data Acquisition) unit. If the system were to expand and control real elevators, or if the simulator were to grow to encompass more than just a PC, the observer class could be replaced with a commercial-off-the-shelf SCADA package without affecting the functionality of the simulator or system.

The operator request menus and the elevator simulation action display should be separate from the collector of the simulation statistics (the observer). The roles and responsibilities of the observer abstraction is then considered. The observer is responsible for keeping track of passengers leaving a floor and entering an elevator, and passengers leaving that elevator and entering a floor. It should also track which floor the passengers came from. The observer should be tied to one elevator, such that it only knows the statistics of that elevator. The abstraction of the observer class is summarized as follows:

Name:

Observer

Responsibilities:

Keep track of the passengers that enter and exit the elevator.

Operations:

Total\_exit\_passengers  
Total\_entry\_passengers  
Passenger\_entry  
Passenger\_exit

Attributes:

Total\_Entry\_Passengers  
Total\_Exit\_Passengers

Since the operator request menus and the elevator simulation action display are separate from the observer, separate abstractions must be defined for each. Another abstraction that will be necessary will be an interface between the observer and the displays. By prototyping some displays during analysis before determining the interface needs, we can de-couple the simulation from the particular display package that might be used. Figure 2 shows one such prototype for the simulation display.

We can, by analyzing the elements in Figure 2, derive an abstraction that can be used to display the simulation. Some of the responsibilities include displaying the passengers per hour information, displaying the static building with elevator shafts and floors, displaying the dynamic elevators traveling up and down the shafts, and displaying passengers entering and exiting the elevator. The abstraction of the draw elevator simulation class is as follows:

Name:

Display\_Elevator\_Simulation

Responsibilities:

Display the passengers per hour information.  
Displaying the static building with elevator shafts and floors.  
Displaying the dynamic elevators traveling up and down the shafts.  
Displaying passengers entering and exiting the elevator.

Operations:

Display\_passenger\_per\_hour  
Display\_static\_building  
Display\_dynamic\_elevator  
Display\_passenger\_entry  
Display\_passenger\_exit

![[User Interface Prototype]](images/elev2.gif)  
Figure 2. Elevator simulator user interface prototype.

The operator request menus can be text based or window based. For simplicity, we will analyze the text based menus. Figure 2 shows one such prototype for the text based menus and prompts display. This abstraction is responsible for displaying the menu and prompting for input. The receipt of input will be in the main body of the program. This abstraction of the text menu and prompts class is summarized as follows:

Name:

Menu\_and\_Prompts

Responsibilities:

Display the menu. Prompt for input.

Operations:

Display\_menu  
Display\_number\_of\_elevators\_prompt  
Display\_print\_reports\_options

![[Text menu prototypes]](images/elev3.gif)  
Figure 3. Text menu prototypes.

Another requirement for the simulator is the final report on the activities of all the major objects. A reporting class will be necessary to print the actual report. We can derive the report information during simulation and pass it to the report class. The report class is responsible for receiving the information and printing the report to the printer or the screen. The report class is summarized as follows:

Name:

Print\_Reports

Responsibilities:

Print report to screen or printer.

Operations:

Print\_Report

Operations:

static\_report\_layout

The report will contain information about the activities of elevator and passengers. It will include totals from each elevator such as the elevator number, the total passengers, the total time, the flow rate and the total number of passengers who exited at each floor. The report will also contain a summary for the building which will be totals of all the elevators. A sample report is shown in Figure 4.

![[Sample Report]](images/elev4.gif)  
Figure 4. A sample report showing the activities of the major objects.

In order to make the output design flexible, we need to de-couple the screen and printer from the report output and from the display output. This will require 2 more classes. These two classes can be derived from a super class dedicated to output. The output class can include such activities as draw text, draw line, draw circle, draw rectangle, set text size, set text style, and set line size. The output class is summarized as follows:

Name:

Output

Responsibilities:

Maintain the commands for output to screen or printer.

Operations (virtual):

Draw\_Text  
Draw\_Line  
Draw\_Circle  
Draw\_Rectangle  
Set\_Text\_Size  
Set\_Text\_Style  
Set\_Line\_Style  
Set\_Line\_Size

Attributes:

line\_style  
line\_size  
text\_style  
text\_size

### Observations

When reading the text about object oriented design, I was inspired. The concepts seemed very simple and easy to follow. However, when it comes to designing my own project, some things didn't make sense any more. The biggest hurdle that I had was discerning between the macro and micro process. I used the example applications as a guide for designing this project. I then tried to follow the micro/macro process. Only when I realized that the micro process occurred at every step of the macro process did things make sense (it wasn't spelled out very clearly in the book). I was then able to break down the steps of the macro process for conceptualization, analysis, and design (evolution and maintenance were beyond the scope of this project), and determine what types of things to do in each for the micro process. The design of the project would have been impossible without the guidance from the example applications.

It was very different to design using an object oriented approach. I am used to using a functional decomposition with structured programming. I found that modeling with objects made the project and concepts easier to understand. Modeling the elevator pieces, parts, activities, etc. was an easy step after identifying the candidate classes and objects. I did have difficulties during the design, due to the nature of my day job as a software engineer. The project at work is very function based. Only spending a few hours on object oriented design every week while working on a function based design for 50 hours a week provided a large challenge. This program was very easy to write after having a design. I did find that the design missed in a few places, and was too complex in some places. However, just having a design made things much easier (I typically don't have this detailed of a design at work).

### Source Code

The source code was written using Turbo C++. It uses the Turbo C++ BGI graphics library, and requires one of the BGI object files to be linked.

[ELEVATOR.ZIP](zip/elevator.zip)

I have modified the code to work with Microsoft VC++ (v1.52).

[MS\_ELEV.ZIP](zip/ms_elev.zip)

I have modified the source code to work with [SDL](http://www.libsdl.org/) - Simple DirectMedia Layer. It is now cross platform and should compile with most any compiler. I have not fully tested it, but have gotten most of it to work under [Debian Linux](http://www.debian.org/) and under Windows with MSVC6.

[sdl-elevator.zip](zip/sdl-elevator.zip)

### References

1.  R. H. Crites and A. G. Barto. (1996) Improving Elevator Performance Using Reinforcement Learning. In: D. S Touretzky, M. C. Mozer, and M. E. Hasselmo, eds., Advances in Neural Information Processing Systems 8. MIT Press, Cambridge MA.
2.  Y. Zhang and A. K. Mackworth. (1996) Design and Analysis of Embedded Real-Time Systems: An Elevator Case Study. Technical Report, Department of Computer Science, University of British Columbia, Vancouver, B.C.
3.  G. Booch. (1994) Object Oriented Analysis and Design with applications. Redwood City, C.A.: The Benjamin/Cummings Publishing Company, Inc.

_This paper - Elevator Simulator Design - was written as a requirement for a C++ and Object Oriented Design class (POS537) at the University of Phoenix, Denver Tech Center Campus, on October 18, 1996_  

* * *

Changes last made on: _Tue 22-Feb-2005_  
