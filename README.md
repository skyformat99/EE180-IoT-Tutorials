# UCLA - Intel Edison - Internet of Things Platform
Contents in this repository came from the [UCLA - Intel Edison - Internet of Things Platform](http://iot.seas.ucla.edu/UCLA-Intel/index.php/UCLA_-_Intel_Edison_-_Internet_of_Things_Platform) site.

### Contents
1. [Our Mission](#our-mission)
2. [Introduction to the "Internet of Things"](#introduction-to-the-internet-of-things)
3. [Tutorials](#tutorials)
4. [Reference Designs](#reference-designs)
	1. Internet of Things: Coordinated Motion System
	2. Internet of Things: Distributed Environmental System
	3. Internet of Things: Machine Learning System
5. [Additional Resources](#additional-resources)

## Our Mission

The UCLA Electrical Engineering Department is dedicated to a mission to introduce Internet of Things (IoT) platforms that provide proven benefits to students at every level from Freshman students in their first quarter at to advanced graduate students. A specific mission focus is to address the acute and unmet need for platforms that enable scaling of instruction to large courses with all students engaged in IoT system development.

To accomplish this goal, in close collaboration with and with the support of Intel Corporation, the UCLA has developed a capable set of resources in support of the Intel Edison IoT platform. These resources include Intel Edison IoT Tutorials that have proven effective at every student level. These provide introduction to IoT for student backgrounds that range from students entering the engineering field to advanced graduate students.

In addition to this, a set of IoT Reference Designs have been developed. The Reference Design provides an advance in IoT system design and engineering experience that has not been previously available.

Reference Designs include:

1. **IoT Machine Learning**: This is a breakthrough enabled by the Edison IoT platform and a new development by our team. These are IoT wireless networked sensor nodes that learn in real time and deliver analytics capability fusing sensor data and other data sources from multiple nodes.
2. **IoT Environmental Monitoring**: This Reference Design provides a full introduction to distributed networked embedded sensor systems including time synchronization.
3. **IoT Coordinated Motion Sensing**: This Reference Design provides a full introduction to coordinated motion sensing that enables multiple nodes to support joint monitoring for human motion characterization, to athletic performance guidance and advancement, and many other applications.

Formal assessment of our IoT course offerings has confirmed effectiveness of this new IoT curriculum at all levels.

## Introduction to the "Internet of Things"

Our team has been fortunate to have benefited from some of the early origins of IoT wtith development of Wireless Sensor Networks where we referred to this new field as “Internetworking the Physical World”. The book, Principles of Embedded Networked System Design by Professors Pottie and Kaiser provides references on this field and fundamental design principles.

Today, the IoT field is growing now at an unprecedented rate with many diverse applications from smartphone to wearable devices. The field of Wireless Health is expanding particularly rapidly with great potential impact on the entire world population. Our Wireless Health devices have been distributed to each continent on earth and are breakthroughs in areas from neurorehabilitation, to monitoring of human digestion, orthopaedics, and even athletics.

We collaborate and develop embedded products for companies as small as entrepreneurial startups to Intel – all with the objectives to advance health and wellness and to support new instruction that speeds student progress and provides students with opportunities for advancement at every level.

We are indebted to Intel for critical support and guidance in this development.

A valuable introduction to IoT that we recommend is this description from Intel: [The Guide to the Internet of Things](https://www.intel.com/content/www/us/en/internet-of-things/infographics/guide-to-iot.html). This described the immense and pervasive impact of IoT and provides students with an appreciation for the role of IoT in their careers ahead.

## Tutorials

These are the Intel Edison IoT Tutorials. Each has been developed to speed your progress and minimize any need for outside assistance – so that each student can proceed independently at any time. We recommend following these Tutorials in the order presented below.

Students familiar with some concepts in the Tutorials should review the Tutorial to ensure their familiarity with all concepts

1. **An Introduction to the Intel Edison Platform, Shell Access and SFTP**
	
		An introduction to the Intel Edison platform, instructions on how to access the shell onboard the Intel Edison, and how to transfer files via SFTP.
	
2. **An Introduction to Linux**

		An introduction (or an important refresher for students with experience) in Linux operations in user space on the Intel Edison platform.
	
3. **An Introduction to OPKG and Vim**
	
		Introduction to methods of IoT platform component installation and an introduction to the vim editor.
	
4. **GPIO, Interrupts, Analog and I2C Interfaces**
	
		Introduction to the MRAA library providing access to General Purpose I/O (GPIO), Interrupts, Analog Sampling and I2C interfaces.
	
5. **PWM, SPI and UART**
	
		Introduction to the MRAA library providing access to digital interfaces including PWM, SPI, and UART.
	
6. **An Introduction to Sockets and Internet Communication**
	
		Introduction (or an important refresher for students with experience) in TCP data transport using a simplified single-thread client-server architecture. Please note that a multi-thread client-server system is included in the Distributed Environmental System Reference Design.
	
7. **An Introduction to IoT Motion Sensing**
	
		Introduction to a 9-Degree of Freedom Sensor (9DOF) including three axes each of acceleration, rotational rate sensing, and magnetic field sensing.
	
8. **An Introduction to Timing Analysis and Synchronization**

		Introduction to analyzing execution time of subsections of code, the cause of drift in clocks, potential pitfalls this drift can cause, and methods to rectify this drift.
	
9. **An Introduction to Kernel Module Development**
	
		Introduction to developing kernel modules on the Intel Edison.
	
10. **An Introduction to Liquid DSP**
	
		Introduction to the C code Liquid-DSP library for applications that require digital signal processing on the Intel Edison board.

## Reference Designs

These are the new IoT Reference Designs. As noted, these provide end – to – end introduction to IoT systems. The Reference Design provides an advance in IoT system design and engineering experience that has not been previously available.

Note that prerequisite tutorials are provided for each Reference Design.

Some student project missions in IoT may benefit from completing two or all three Reference Designs.

1. **Internet of Things: Coordinated Motion System**

		Prerequisite tutorials: 1, 2, 3, 4, 6, 7, 8
	
2. **Internet of Things: Distributed Environmental System**
	
		Prerequisite tutorials: 1, 2, 3, 4, 6, 7
	
3. **Internet of Things: Machine Learning System**

		Prerequisite tutorials: 1, 2, 3, 4

## Additional Resources

1. **An Introduction to C**

		Introduction or (or an important refresher for students with experience) for C code development including the gcc compiler.

2. **Installing Miniconda on the Intel Edison including the SciPy and NumPy tools**
	
		Methods for Installing Miniconda for Python Package Management.

3. **Intel Cloud-Based Analytics**
	
		These documents will teach you how to use the Intel Cloud Analytics service, HTTP and REST interfaces.

4. **Additional Sparkfun Components**
    
		Programming guides on how to interface with the GPIO and ADC Sparkfun blocks.

5. **Audio Interface**
    
		Programming and Hardware setup guide for getting audio information onto your Intel Edison.

6. **Troubleshooting Guide**
    
		If you have any issues with the Intel Edison, please check this guide.

7. **Full NTP Installation**
    
		Instructions on how to synchronize multiple client Intel Edison nodes to a single Intel Edison server node
