### 2.3. State Chart Diagram ###
Represents the system as a state machine.

#### 2.3.1. State ####
A snapshot of the system at a given time.

![Class](notation/state/state-1.png)

#### 2.3.2. State Transitions ####

Every state machine have an initial state.

![Class](notation/state/state-2.png)

Every state machine have a terminal state.

![Class](notation/state/state-3.png)

System moves from one state to another state up on a trigger/event/etc., 

![Class](notation/state/state-4.png)

The triggered transition may happen only if a pre-condition is satisfied.

![Class](notation/state/state-5.png)

Each system may take certain actions upon entering a state, while in the given state and while leaving the state.

![Class](notation/state/state-6.png)

#### 2.3.3. Kinds of States ####

A composite state is a super state of several sub states.

![Class](notation/state/state-9.png)

Illustration: Composite State

![Class](notation/state/state-10.png)

Transition to a compisite state always invokes the first sub state unless specified. A history vertex enables transition to the last active state, instead.

![Class](notation/state/state-11.png)

A substatemachine is a re-usable unit like procedure.

![Class](notation/state/state-8.png)

An orthogonal state is a composite state with parallel transitions.

![Class](notation/state/state-7.png)

Illustration: Orthogonal state

![Class](notation/state/state-12.png)