
#include "reactor-uc/reactor-uc.h"

// Reaction structs
DEFINE_REACTION_STRUCT(Reactor_Shutdown, reaction0, 0);
DEFINE_REACTION_STRUCT(Reactor_Shutdown, reaction1, 0);

// Timer structs 
// TODO: You need to define the timer struct here!
DEFINE_STARTUP_STRUCT(Reactor_Shutdown, 1, 0);
DEFINE_SHUTDOWN_STRUCT(Reactor_Shutdown, 1, 0);
// Port structs

// Connection structs

//The reactor self struct
typedef struct {
  Reactor super;
  // Child reactor fields
  
  REACTION_INSTANCE(Reactor_Shutdown, reaction0);
  REACTION_INSTANCE(Reactor_Shutdown, reaction1);
  // Timers
  // TODO: The timer should be part of this reactor struct
  // Actions and builtin triggers
  
  STARTUP_INSTANCE(Reactor_Shutdown);SHUTDOWN_INSTANCE(Reactor_Shutdown);
  // Connections 
  
  // Ports 
  
  // State variables 
  // Reactor parameters
  
  // TODO: this needs to be updated
  REACTOR_BOOKKEEPING_INSTANCES(2, 2, 0);
} Reactor_Shutdown;

REACTOR_CTOR_SIGNATURE(Reactor_Shutdown);


// Reaction bodies
DEFINE_REACTION_BODY(Reactor_Shutdown, reaction0) {
  // Bring self struct, environment, triggers, effects and sources into scope.
  SCOPE_SELF(Reactor_Shutdown);
  SCOPE_ENV();
  SCOPE_STARTUP(Reactor_Shutdown);
  // TODO: You need to scope the timer here
         
  // Start of user-witten reaction body
  printf("startup ...");
}
DEFINE_REACTION_BODY(Reactor_Shutdown, reaction1) {
  // Bring self struct, environment, triggers, effects and sources into scope.
  SCOPE_SELF(Reactor_Shutdown);
  SCOPE_ENV();
  SCOPE_SHUTDOWN(Reactor_Shutdown);
         
  // Start of user-witten reaction body
  printf("shutdown ...");
}
// Reaction constructors
DEFINE_REACTION_CTOR(Reactor_Shutdown, reaction0, 0);
DEFINE_REACTION_CTOR(Reactor_Shutdown, reaction1, 1);
DEFINE_STARTUP_CTOR(Reactor_Shutdown);
DEFINE_SHUTDOWN_CTOR(Reactor_Shutdown);
// Timer constructors 
// TODO: You need to construct the timer here!

// Port constructors

// Connection constructors

REACTOR_CTOR_SIGNATURE(Reactor_Shutdown) {
   REACTOR_CTOR_PREAMBLE();
   REACTOR_CTOR(Reactor_Shutdown);
   // Initialize Reactor parameters
   
        
   // Initialize Timers
   // TODO: You need to initialize the timer here!
   // Initialize actions and builtin triggers
   
   INITIALIZE_STARTUP(Reactor_Shutdown);
   INITIALIZE_SHUTDOWN(Reactor_Shutdown);
   // Initialize ports
   
   // Initialize connections
   
   // Initialize connections
   
   // Initialize Reactions 
   INITIALIZE_REACTION(Reactor_Shutdown, reaction0);
     STARTUP_REGISTER_EFFECT(self->reaction0);
     // TODO: reaction0 now can be triggered by the timer
           
           
   INITIALIZE_REACTION(Reactor_Shutdown, reaction1);
     SHUTDOWN_REGISTER_EFFECT(self->reaction1);
           
}

ENTRY_POINT(Reactor_Shutdown, FOREVER, false);

int main(int argc, char **argv) {
   lf_start();
}
