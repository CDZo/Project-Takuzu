#include "TestPawn.h"

TestPawn::TestPawn()
{
    should_return_true_when_pawn_with_same_state_are_compared();

    std::cout << "Tests for pawn: ok" << std::endl;
}

void TestPawn::should_return_true_when_pawn_with_same_state_are_compared()
{
    Pawn p1,p2;
    assert(p1 == p2);
}
