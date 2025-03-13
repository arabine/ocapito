#include "Application.h"


int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  Application app;

  app.Initialize();

  app.Loop();

  return 0;
}
