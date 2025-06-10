#pragma once

#include <interface/commands/BaseCommand.hpp>

class CompositeCommand : public BaseCommand
{
  public:
    void add(std::shared_ptr<BaseCommand> command) override;
    void remove(iterator &iter) override;

    iterator begin() const override;
    iterator end() const override;

    bool isComposite() override;

    void execute() const override;

  private:
    std::list<std::shared_ptr<BaseCommand>> commands;
};
