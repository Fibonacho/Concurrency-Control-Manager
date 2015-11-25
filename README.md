# Concurrency-Control-Manager

-----------
Description
-----------

In this assignment we will imitate a concurrency control manager of a DBMS. We 
stick to our booking system scenario and extend it by more queries. The task is 
to implement the relations (using a suitable data structures) and a concurrency 
manager which will manage the access to the relations by locking and unlocking
instructions.

We simplify the schema of our database as much as possible. Our database 
consists of the following relations (with all attributes being integers):
- flights[flight_id]
- seats[seat_id, flight_id]
- passengers[passenger_id]
- reservations[passenger_id, seat_id, flight_id]

There should be multiple flights with varying passengers capacity. A passenger
can book more flights, but each flight only once.

Decide on the cardinality of the relations such that the locking manager will 
have some work to do, i.e., the runtimes will be visible and comparable in the 
experiments. Add also delays (sleep command) for each transaction to simulate 
the access time to the database.

There should be multiple transaction threads with the following structure:
  
  repeat some number of times:
    select a transaction type randomly
    select object(flight and passenger id) for transaction randomly
    invoke transaction

The following transactions should be supported:
- book(flight_id, passenger_id): book a seat for a passenger on a flight
- cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
- my_flights(passenger_id): return the set of flights on which a passenger has 
  a reservation
- total_reservations(): return the total sum of all reservations on all flights

The transactions should be invoked only for existing data, i.e., the parameter
values for the transactions must exist. Otherwise, if a transaction is 
performed on non-existing data, it should have no influence.

--------
Schedule
--------

We split this assignment into multiple steps, each with a separate deadline and
points to earn. You'll get a feedback after each step.

Step 1 - Implement database and transactions (1 point, deadline 30.11.2015 08:59).

  Implement the data structures to store the relations and decide on the
  respective cardinalities. Decide on the distribution and cardinalities of
  the transactions. The data structures must contain no synchronization code. 
  The concurrency control manager must implement the mechanism to control access 
  to the data structures. 

Step 2 - Implement serial schedules (1 point, deadline 07.12.2015 08:59).

  Run all transactions serially in their incoming order. Imitate database-level
  locks.

Step 3 - Implement two-phase locking (2 points, deadline 14.12.2015 08:59).

  Implement the transactions such that they comply to two-phase locking at 
  a finer-granularity level (table/tuple locks). Exploit semantics of the
  operations to allow as much concurrency as possible.  

Step 4 - Make experiments and final report (1 point, deadline 21.12.2015 08:59).

  Experiment on your implementation. Compare the versions of Steps 2 and 3. In 
  particular, plot (a) the impact of number of transaction threads on throughput, 
  and (b) the impact of the transaction distribution on throughput. Throughput 
  is the number of transactions completed over a specific time. The number 
  of transaction threads should be increased to a sufficient number to see 
  a trend on the performance graphs. 

COMMENT: If you are faster with one step, use the remaining time to the deadline
         for a consecutive step.

COMMENT: The steps overlap and the design choices influence multiple steps.

COMMENT: Any concerns or problems should be posted on Piazza, such that each 
         team has an immediate access to this information.
