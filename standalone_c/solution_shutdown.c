
#include "reactor-uc/reactor-uc.h"

typedef struct {
  BuiltinTrigger super;
  Reaction *effects[1];  // For storing pointers to the reactions triggered by
                         // startup.
} MyStartupTrigger;

typedef struct {
  BuiltinTrigger super;
  Reaction *effects[1];  // For storing pointers to the reactions triggered by
                         // startup.
} MyShutdownTrigger;


typedef struct {
  Reactor super;
  Reaction reaction_startup;
  Reaction reaction_shutdown;
  MyStartupTrigger startup;
  MyShutdownTrigger shutdown;
  Trigger *triggers[2];  // For storing pointers to all the triggers within this
                         // reactor.
  Reaction *reactions[2];  // For storing pointers to all the reactions within
                           // this reactor.
} MyReactor;

// Reaction body
void on_startup(Reaction *self) { printf("Hello, World!\n"); }
void on_shutdown(Reaction *self) { printf("Goodbye, World!\n"); }

// The "environment" contains reaction queue, event queue, scheduler.
Environment env;

// Top-level reactor, the entire reactor program is nested within this structure
MyReactor reactor;

int main() {
  Environment_ctor(&env, &reactor.super);
  Reactor_ctor(&reactor.super, "MyReactor", &env, NULL, NULL, 0,
               reactor.reactions, 2, reactor.triggers, 2);

  // Configure the startup trigger
  reactor.startup.effects[0] = &reactor.reaction_startup;
  BuiltinTrigger_ctor(&reactor.startup.super, TRIG_STARTUP, &reactor.super,
                      reactor.startup.effects, 1, NULL, 0);

  // Configure the shutdown trigger
  reactor.shutdown.effects[0] = &reactor.reaction_shutdown;
  BuiltinTrigger_ctor(&reactor.shutdown.super, TRIG_SHUTDOWN, &reactor.super,
                      reactor.shutdown.effects, 1, NULL, 0);

  // Configure the reaction
  Reaction_ctor(&reactor.reaction_startup, &reactor.super, on_startup, NULL, 0, 0);
  Reaction_ctor(&reactor.reaction_shutdown, &reactor.super, on_shutdown, NULL, 0, 1);

  // Configure the reactor
  reactor.triggers[0] = &reactor.startup.super.super;
  reactor.triggers[1] = &reactor.shutdown.super.super;
  reactor.reactions[0] = &reactor.reaction_startup;
  reactor.reactions[1] = &reactor.reaction_shutdown;

  // Assemble reactor programs and compute levels
  env.assemble(&env);

  // Run the program.
  env.start(&env);
}
