#include "TestModel.h"
#include "ModelTakuzu.h"
#include <iostream>
#include <assert.h>

//enum State {empty, black, white};
TestModel::TestModel()
{
    std::cout << "TestModel constructor" <<std::endl;
    should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns();
    should_return_gridsize_when_pawns_are_correctly_set_in_lign();
    should_return_gridsize_when_testing_ligns_with_pawns_set_in_column();
    should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();

    std::cout << "All Tests ok" << std::endl;
}

void TestModel::should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns()
{
    ModelTakuzu model(nullptr);
    model.setSize(6);
    model.initGrid(6);
    assert(model.putInGrid(5,3,1) == true);
    assert(model.putInGrid(5,4,1) == true);
    assert(model.putInGrid(5,5,1) == true);
    assert(model.checkLignSideBySidePawn() == 5);
}

void TestModel::should_return_gridsize_when_pawns_are_correctly_set_in_lign()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(2,3,1) == true);
    assert(model.putInGrid(2,4,1) == true);
    assert(model.checkLignSideBySidePawn() == size);
}

void TestModel::should_return_gridsize_when_testing_ligns_with_pawns_set_in_column()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,3,1) == true);
    assert(model.putInGrid(1,3,1) == true);
    assert(model.putInGrid(2,3,1) == true);
    assert(model.checkLignSideBySidePawn() == size);
}

void TestModel::should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns()
{
    ModelTakuzu model(nullptr);
    model.setSize(6);
    model.initGrid(6);
    assert(model.putInGrid(0,4,1) == true);
    assert(model.putInGrid(1,4,1) == true);
    assert(model.putInGrid(2,4,1) == true);
    assert(model.checkColumnSideBySidePawn() == 4);
}


