#include <Options.hpp>
#include <Controller.hpp>
#include <displayer.hpp>

int main(int argc, char **argv) {
  auto options = model::Options(argc, argv);

  Controller controller(options);

  auto ls_dirinfos = controller.create_models();

  Displayer::Displayer displayer(options);

  displayer.display(ls_dirinfos);
}
