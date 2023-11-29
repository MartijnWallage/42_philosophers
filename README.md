# 42 Philosophers

This program is a project of the 42 School, called "Philosophers", and based on the Dining Philosophers Problem for concurrent computing.


## Problem

A number of philosophers sit around a table, each with a bowl of spaghetti in front of them, and just one fork.
However, they absolutely refuse to eat with just one fork.
They are only able to start eating their spaghetti when they have *two* forks.
(Don't ask why – I guess forks to them are what chopsticks are to the less philosophically inclined.)
So (oddly unfazed by questions of hygiene) they eat when they manage to get of the fork of their left or right neighbour, as well as of their own fork, of course, which is ever in danger of being taken by one of those neighbours.
After they are done eating, they sleep, and when they are done sleeping, they wake up and think until they can get hold of two forks again.
If they don't eat in time, they die.
What policy for taking forks should they implement so that none of them die, or at least, so that none of them die needlessly?
They have to make these important decisions all by themselves; they never talk to each other.

I like this problem for two reasons. 
One, it was invented by Edsger W. Dijkstra, the Ludwig Wittgenstein of computer science. 
Two, it is about philosophers, and I used to be an academic philosopher. 
(My favourite philosopher, incidentally, is Ludwig Wittgenstein, the Edsger W. Dijkstra of philosophy.)
But this funny scenario also represents a real problem about running different processes or threads simultaneously within one program.

## Threads and Data Races

In the non-bonus part of the project (see the /philo folder), there is a *thread* for each philosopher.
A thread is a somewhat independent control flow, which still shares memory space with the other threads in the same process.
Since threads access the same memory space, different threads can access (check or change) the same bit of memory (the same variable) simultaneously.
That is called a *data race*, and it needs to be avoided.
You can see why: imagine Thread A checks a conditional that depends on the value of some variable `x` (say, `x < 100`).
A checks the conditional, finds it satisfied, and proceeds to the consequent.
But in the meantime, Thread B has changed the value of `x`, invalidating the conditional!
Chaos would ensue.
Our program would no longer be deterministic.
We don't want that.

## Mutex

The way to avoid data races is put a kind of lock, called a *mutex*, on each shared variable.
When a thread wants to check or change the variable, it first locks the mutex; while the mutex is locked, no other threads can get past this point in the code.
When the thread is done checking or changing the variable, it unlocks the mutex; now the next thread can proceed.
Let's get back to our scenario.
We can think of the forks as variables protected by a mutex.
But philosophers like identity statements, so let's give them the satisfaction of saying that a fork *just is* (the very same thing as) a mutex.

Doesn't that feel good?

## Deadlock

Aside from preventing data races, we must prevent *deadlock*.
A deadlock is what would happen if philosopher 1 picks up the fork of philosopher 2, who in turn, though deprived of his own fork, picks up the fork of philosopher 3, who in turn ... and so on until the last philosopher, who would deprive philosopher 1 of his own fork.
There are various strategies for preventing deadlock, which I don't want to spoil.

## What doesn’t kill you..

Finally, we must let the philosophers eat as often as they can within these bounds, so that they don't die.
The program is run by setting the number of philosophers, the time (in milliseconds) that they can live without eating, the time it takes them to eat, the time it takes them to sleep, and an optional last argument that determines the numbers of meals after which the simulation will stop.
If the user sets these parameters in such a way that the philosophers won't be able to survive, no matter how clever their policy for picking up forks, our program should make sure that they die at the right time.

## Bonus

In the bonus part of the project (see the /philo_bonus folder), there is a *process* for each philosopher.
Instead of a mutex for each fork, we use a *semaphor* with the value of the number of forks/philosophers.
This makes some things easier and some things harder.
On the whole, it is definitely the most time-expensive bonus I have encountered at 42, since it's basically a whole new program.
