# Handling-Zombies

The purpose of the zombie state is to maintain information about the child for the parent to fetch at some later time. This information includes the process ID of the child, its termination status, and the information on the resource utilization of the child(CPU time, memory, etc.)

If a process terminates, and that process has children in the zombie state, the parent process ID of all zombie children is set to 1 (the init process), which will inherit the children and clean them.

But in our concurrent server, since the parent is still alive, the children remains as zombies.

Whenever we fork children, we must wait for them to prevent them from becoming zombies.

To do this, we establish a signal handler to catch SIGCHILD and within the handler, we call wait.
