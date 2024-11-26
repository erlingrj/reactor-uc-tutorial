#include "reactor-uc/reactor-uc.h"

typedef struct {
  BuiltinTrigger super;
  Reaction *effects[1];  // For storing pointers to the reactions triggered by
                         // startup.
} MyStartupTrigger;

typedef struct {
  Reactor super;
  Reaction reaction;
  MyStartupTrigger startup;
  Trigger *triggers[1];  // For storing pointers to all the triggers within this
                         // reactor.
  Reaction *reactions[1];  // For storing pointers to all the reactions within
                           // this reactor.
} MyReactor;

// Reaction body
void on_startup(Reaction *self) { printf("Hello, World!\n"); }

// The "environment" contains reaction queue, event queue, scheduler.
Environment env;

// Top-level reactor, the entire reactor program is nested within this structure
MyReactor reactor;

int main() {
  Environment_ctor(&env, &reactor.super);
  Reactor_ctor(&reactor.super, "MyReactor", &env, NULL, NULL, 0,
               reactor.reactions, 1, reactor.triggers, 1);

  // Configure the startup trigger
  reactor.startup.effects[0] = &reactor.reaction;
  BuiltinTrigger_ctor(&reactor.startup.super, TRIG_STARTUP, &reactor.super,
                      reactor.startup.effects, 1, NULL, 0);

  // Configure the reaction
  Reaction_ctor(&reactor.reaction, &reactor.super, on_startup, NULL, 0, 0);

  // Configure the reactor
  reactor.triggers[0] = &reactor.startup.super.super;
  reactor.reactions[0] = &reactor.reaction;

  // Assemble reactor programs and compute levels
  env.assemble(&env);

  // Run the program.
  env.start(&env);
}
