### 2.2. Activity Diagram ###
Represents a workflow in the system.

#### 2.2.1. Action ####
A workflow/activity is a set of actions arranged in a logical order.

![Class](notation/activities/activity-1.png)

#### 2.2.2. Activity Flows ####

Every activity starts from an "initial action".

![Class](notation/activities/activity-2.png)

Every activity ends with a "terminal action".

![Class](notation/activities/activity-3.png)

Usually, the control of an activity is passed from one action to another action.

![Class](notation/activities/activity-4.png)

Sometimes, the control of an activity is passed to the actions based on conditions.

![Class](notation/activities/activity-5.png)

Often, several action paths might merge at a common point also.

![Class](notation/activities/activity-6.png)

Also, the control of an activity might be passed to multiple actions in parallel.

![Class](notation/activities/activity-7.png)

Similarly, several action paths join together before passing the control to the next action.

![Class](notation/activities/activity-8.png)

#### 2.2.3. Activity Partitions ####

Several actions might be grouped together for better readability.

![Class](notation/activities/activity-9.png)

#### 2.2.4. Special Actions ####

An action might be part of an interruptable region.

![Class](notation/activities/activity-10.png)

An action can be very complex which demands further granularity.

![Class](notation/activities/activity-11.png)

An action might be asynchronous as well.

![Class](notation/activities/activity-12.png)

Sometimes, delay/wait/etc., might also needs to be represented.

![Class](notation/activities/activity-13.png)

It is also possible to show an object flow between actions.

![Class](notation/activities/activity-14.png)

Exception handlers are special actions.

![Class](notation/activities/activity-15.png)

As an alternative to object flows, input/output pins are also used.

![Class](notation/activities/activity-16.png)

Illustration of pins:

![Class](notation/activities/activity-17.png)

#### 2.2.5. Activity Illustrations ####

Illustration-1:

![Class](notation/activities/activity-18.png)

Illustration-2:

![Class](notation/activities/activity-19.png)

Illustration-3:

![Class](notation/activities/activity-20.png)

Illustration-4:

![Class](notation/activities/activity-21.png)