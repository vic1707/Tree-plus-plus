#pragma once
/* std */
#include <string>
/* custom */
#include <displayers_specs/Filter.hpp>

namespace Filter {
  class Extensions : public AFilter {
    private:
      std::vector<std::string> m_discriminants;
    public:
      void filter(Items &items) final {
        for (auto it = items.begin(); it != items.end(); ++it) {
          if (std::find(m_discriminants.begin(), m_discriminants.end(), this->get_extension(*it)) != m_discriminants.end()) return;
          items.erase(it);
          --it;
        }
      }
    private:
      std::string get_extension(const auto &i) {
        if (std::holds_alternative<FileDirInfos::DirInfos>(i))
          return std::get<FileDirInfos::DirInfos>(i).name.extension;
        else
          return std::get<FileDirInfos::FileInfos>(i).name.extension;
      };
  };
} // namespace Filter