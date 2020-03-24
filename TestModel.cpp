#include "TestModel.h"
#include "ModelTakuzu.h"
#include <iostream>
#include <assert.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2
//enum State {empty, black, white};
TestModel::TestModel()
{
    std::cout << "TestModel constructor" <<std::endl;
    should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns();
    should_return_gridsize_when_pawns_are_correctly_set_in_lign();
    should_return_gridsize_when_testing_ligns_with_pawns_set_in_column();
    should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();
    should_return_gridsize_when_pawns_are_correctly_set_in_column();
    should_return_gridsize_when_testing_columns_with_pawns_set_in_lign();
    should_return_gridsize_when_all_ligns_are_balanced();
    should_return_lign_when_it_is_unbalanced();
    should_return_gridsize_when_all_columns_are_balanced();

    std::cout << "All Tests ok" << std::endl;
}

void TestModel::should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns()
{
    ModelTakuzu model(nullptr);
    model.setSize(6);
    model.initGrid(6);
    assert(model.putInGrid(5,3,BLACK) == true);
    assert(model.putInGrid(5,4,BLACK) == true);
    assert(model.putInGrid(5,5,BLACK) == true);
    assert(model.checkLignSideBySidePawn() == 5);
}

void TestModel::should_return_gridsize_when_pawns_are_correctly_set_in_lign()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(2,3,WHITE) == true);
    assert(model.putInGrid(2,4,WHITE) == true);
    assert(model.checkLignSideBySidePawn() == size);
}

void TestModel::should_return_gridsize_when_testing_ligns_with_pawns_set_in_column()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,3,WHITE) == true);
    assert(model.putInGrid(1,3,WHITE) == true);
    assert(model.putInGrid(2,3,WHITE) == true);
    assert(model.checkLignSideBySidePawn() == size);
}

void TestModel::should_return_gridsize_when_pawn_between_pawns_of_different_colors()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(5,3,BLACK) == true);
    assert(model.putInGrid(5,4,WHITE) == true);
    assert(model.putInGrid(5,5,BLACK) == true);
    assert(model.checkLignSideBySidePawn() == size);
}

void TestModel::should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,4,WHITE) == true);
    assert(model.putInGrid(1,4,WHITE) == true);
    assert(model.putInGrid(2,4,WHITE) == true);
    assert(model.checkColumnSideBySidePawn() == 4);
}

void TestModel::should_return_gridsize_when_pawns_are_correctly_set_in_column()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,4,WHITE) == true);
    assert(model.putInGrid(1,4,WHITE) == true);
    model.display();
    assert(model.checkColumnSideBySidePawn() == size);
}

void TestModel::should_return_gridsize_when_testing_columns_with_pawns_set_in_lign()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,4,WHITE) == true);
    assert(model.putInGrid(0,5,WHITE) == true);
    assert(model.checkColumnSideBySidePawn() == size);
}

void TestModel::should_return_gridsize_when_all_ligns_are_balanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,1,BLACK) == true);
    assert(model.putInGrid(0,4,WHITE) == true);
    assert(model.putInGrid(1,5,WHITE) == true);
    //assert(model.checkNumberLign() == size);

}

void TestModel::should_return_lign_when_it_is_unbalanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(1,5,WHITE) == true);
    assert(model.putInGrid(3,1,WHITE) == true);
    assert(model.putInGrid(3,4,WHITE) == true);
    //assert(model.checkNumberLign() == 3);
}

void TestModel::should_return_gridsize_when_all_columns_are_balanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(1,5,WHITE) == true);
    assert(model.putInGrid(3,1,WHITE) == true);
    assert(model.putInGrid(3,4,BLACK) == true);
    assert(model.putInGrid(3,4,WHITE) == true);
model.display();
   // assert(model.checkNumberLign() == 3);
}


