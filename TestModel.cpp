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
    should_return_true_when_put_pawn_in_boundary();
    should_return_false_when_put_pawn_out_out_of_bounds();

    should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns();
    should_return_gridsize_when_pawns_are_correctly_set_in_lign();
    should_return_gridsize_when_testing_ligns_with_pawns_set_in_column();
    should_return_gridsize_when_pawn_between_pawns_of_different_colors();

    should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();
    should_return_gridsize_when_pawns_are_correctly_set_in_column();
    should_return_gridsize_when_testing_columns_with_pawns_set_in_lign();

    should_return_gridsize_when_all_ligns_are_balanced();
    should_return_lign_when_it_is_unbalanced();

    should_return_gridsize_when_all_columns_are_balanced();
    should_return_column_when_it_is_unbalanced();

    should_return_gridsize_when_all_columns_are_unique();
    should_return_gridsize_when_columns_are_unique_but_ligns_not();
    should_return_faulty_column_when_uniqueness_is_not_respected();

    should_return_gridsize_when_all_ligns_are_unique();
    should_return_gridsize_when_ligns_are_correct_but_columns_not();
    should_return_faulty_lign_when_uniqueness_is_not_respected();
    std::cout << "Tests for model: ok" << std::endl;
}

void TestModel::should_return_true_when_put_pawn_in_boundary()
{
    ModelTakuzu model(nullptr);
    model.setSize(6);
    model.initGrid(6);
    assert(model.putInGrid(5,3,BLACK) == true);
    assert(model.putInGrid(5,4,BLACK) == true);
    assert(model.putInGrid(5,5,BLACK) == true);
}

void TestModel::should_return_false_when_put_pawn_out_out_of_bounds()
{
    ModelTakuzu model(nullptr);
    int size = 6;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(-1,0,BLACK) == false);
    assert(model.putInGrid(size,0,BLACK) == false);

    assert(model.putInGrid(0,-1,BLACK) == false);
    assert(model.putInGrid(0,size,BLACK) == false);

    assert(model.putInGrid(-1,-1,BLACK) == false);
    assert(model.putInGrid(size,size,BLACK) == false);
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
    assert(model.putInGrid(1,4,BLACK) == true);
    assert(model.checkBalancedNumberLign() == size);

}

void TestModel::should_return_lign_when_it_is_unbalanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(3,1,WHITE) == true);
    assert(model.putInGrid(3,4,WHITE) == true);
    assert(model.checkBalancedNumberLign() == 3);
}

void TestModel::should_return_gridsize_when_all_columns_are_balanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,1,WHITE) == true);
    assert(model.putInGrid(1,1,BLACK) == true);
    assert(model.putInGrid(3,4,BLACK) == true);
    assert(model.putInGrid(4,4,WHITE) == true);
    assert(model.checkBalancedNumberColumn() == size);
}

void TestModel::should_return_column_when_it_is_unbalanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,1,WHITE) == true);
    assert(model.putInGrid(1,1,BLACK) == true);
    assert(model.putInGrid(3,4,BLACK) == true);
    assert(model.putInGrid(4,4,BLACK) == true);

    assert(model.checkBalancedNumberColumn() == 4);
}

void TestModel::should_return_gridsize_when_all_columns_are_unique()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,WHITE) == true);
    assert(model.putInGrid(0,1,BLACK) == true);
    assert(model.putInGrid(1,0,BLACK) == true);
    assert(model.putInGrid(1,1,WHITE) == true);
    std::set<std::pair<int,int>> column;
    column.insert(std::make_pair(size,size));
    assert(model.isAllColumnUnique() == column);
}

void TestModel::should_return_gridsize_when_columns_are_unique_but_ligns_not()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,WHITE) == true);
    assert(model.putInGrid(0,1,BLACK) == true);
    assert(model.putInGrid(0,2,WHITE) == true);
    assert(model.putInGrid(1,0,BLACK) == true);
    assert(model.putInGrid(1,1,WHITE) == true);
    assert(model.putInGrid(1,2,WHITE) == true);
    assert(model.putInGrid(2,0,BLACK) == true);
    assert(model.putInGrid(2,1,WHITE) == true);
    assert(model.putInGrid(2,2,WHITE) == true);
    std::set<std::pair<int,int>> column;
    column.insert(std::make_pair(size,size));
    assert(model.isAllColumnUnique() == column);
}

void TestModel::should_return_faulty_column_when_uniqueness_is_not_respected()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,WHITE) == true);
    assert(model.putInGrid(0,1,WHITE) == true);
    assert(model.putInGrid(0,2,WHITE) == true);

    assert(model.putInGrid(1,0,BLACK) == true);
    assert(model.putInGrid(1,1,BLACK) == true);
    assert(model.putInGrid(1,2,BLACK) == true);

    std::set<std::pair<int,int>> wrongColumn;
    wrongColumn.insert(std::make_pair(0,1));
    wrongColumn.insert(std::make_pair(1,2));
    assert(model.isAllColumnUnique() == wrongColumn);
}

void TestModel::should_return_gridsize_when_all_ligns_are_unique()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,WHITE) == true);
    assert(model.putInGrid(0,1,BLACK) == true);
    assert(model.putInGrid(1,0,BLACK) == true);
    assert(model.putInGrid(1,1,WHITE) == true);
    std::set<std::pair<int,int>> lign;
    lign.insert(std::make_pair(size,size));
    assert(model.isAllLignUnique() == lign);
}

void TestModel::should_return_gridsize_when_ligns_are_correct_but_columns_not()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,BLACK) == true);//
    assert(model.putInGrid(0,1,WHITE) == true);
    assert(model.putInGrid(0,2,WHITE) == true);
    assert(model.putInGrid(1,0,WHITE) == true);
    assert(model.putInGrid(1,1,BLACK) == true);
    assert(model.putInGrid(1,2,BLACK) == true);
    assert(model.putInGrid(2,0,WHITE) == true);
    assert(model.putInGrid(2,1,WHITE) == true);
    assert(model.putInGrid(2,2,WHITE) == true);
    std::set<std::pair<int,int>> lign;
    lign.insert(std::make_pair(size,size));
    assert(model.isAllLignUnique() == lign);
}

void TestModel::should_return_faulty_lign_when_uniqueness_is_not_respected()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;
    model.setSize(size);
    model.initGrid(size);
    assert(model.putInGrid(0,0,BLACK) == true);//
    assert(model.putInGrid(0,1,BLACK) == true);
    assert(model.putInGrid(1,0,BLACK) == true);
    assert(model.putInGrid(1,1,BLACK) == true);
    std::set<std::pair<int,int>> lign;
    lign.insert(std::make_pair(0,1));
    assert(model.isAllLignUnique() == lign);
}


