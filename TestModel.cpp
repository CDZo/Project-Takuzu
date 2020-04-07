#include "TestModel.h"
#include "ModelTakuzu.h"
#include <iostream>
#include <assert.h>

#define EMPTY 0
#define BLACK 1
#define WHITE 2
#include "Constant.h"
//enum State {empty, black, white};
TestModel::TestModel()
{
    should_return_true_when_put_pawn_in_boundary();
    should_return_false_when_put_pawn_out_out_of_bounds();

    should_return_position_of_faulty_pawns_when_3pawns_are_side_by_side_in_rows();
    should_return_empty_set_when_pawns_are_correctly_set_in_row();
    should_return_empty_set_when_testing_rows_with_pawns_set_in_column();
    should_return_empty_set_when_pawn_between_pawns_of_different_colors();

    should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();
    should_return_empty_set_when_pawns_are_correctly_set_in_column();
    should_return_empty_set_when_testing_columns_with_pawns_set_in_row();

    should_return_empty_set_when_all_rows_are_balanced();
    should_return_rows_when_they_are_unbalanced();

    should_return_empty_set_when_all_columns_are_balanced();
    should_return_column_when_it_is_unbalanced();

    should_return_empty_set_when_all_columns_are_unique();
    should_return_empty_set_when_columns_are_unique_but_rows_not();
    should_return_faulty_column_when_uniqueness_is_not_respected();

    should_return_empty_set_when_all_rows_are_unique();
    should_return_empty_set_when_rows_are_correct_but_columns_not();
    should_return_faulty_row_when_uniqueness_is_not_respected();

    should_return_true_when_grid_is_correctly_finished();
    std::cout << "Tests for model: ok" << std::endl;
}

void TestModel::should_return_true_when_put_pawn_in_boundary()
{
    ModelTakuzu model(nullptr);

    model.initGrid(6);
    assert(model.putInGrid(5,3,State::Black));
    assert(model.putInGrid(5,4,State::Black));
    assert(model.putInGrid(5,5,State::Black));
}

void TestModel::should_return_false_when_put_pawn_out_out_of_bounds()
{
    ModelTakuzu model(nullptr);
    int size = 6;

    model.initGrid(size);
    assert(model.putInGrid(-1,0,State::Black) == false);
    assert(model.putInGrid(size,0,State::Black) == false);

    assert(model.putInGrid(0,-1,State::Black) == false);
    assert(model.putInGrid(0,size,State::Black) == false);

    assert(model.putInGrid(-1,-1,State::Black) == false);
    assert(model.putInGrid(size,size,State::Black) == false);
}

void TestModel::should_return_position_of_faulty_pawns_when_3pawns_are_side_by_side_in_rows()
{
    ModelTakuzu model(nullptr);
    int size = 3;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::Black));
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(0,2,State::Black));

    assert(model.putInGrid(1,0,State::White));
    assert(model.putInGrid(1,1,State::White));
    assert(model.putInGrid(1,2,State::White));

    std::set<std::pair<int,int>> faultyPawns;
    faultyPawns.insert(std::make_pair(0,0));
    faultyPawns.insert(std::make_pair(0,1));
    faultyPawns.insert(std::make_pair(0,2));
    faultyPawns.insert(std::make_pair(1,0));
    faultyPawns.insert(std::make_pair(1,1));
    faultyPawns.insert(std::make_pair(1,2));
    assert(model.checkRowSideBySidePawn() == faultyPawns);
}

void TestModel::should_return_empty_set_when_pawns_are_correctly_set_in_row()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(2,3,State::White));
    assert(model.putInGrid(2,4,State::White));
    std::set<std::pair<int,int>> pawns = model.checkRowSideBySidePawn();
    assert(pawns.empty());
}

void TestModel::should_return_empty_set_when_testing_rows_with_pawns_set_in_column()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,3,State::White));
    assert(model.putInGrid(1,3,State::White));
    assert(model.putInGrid(2,3,State::White));
    std::set<std::pair<int,int>> pawns = model.checkRowSideBySidePawn();
    assert(pawns.empty());
}

void TestModel::should_return_empty_set_when_pawn_between_pawns_of_different_colors()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(5,3,State::Black));
    assert(model.putInGrid(5,4,State::White));
    assert(model.putInGrid(5,5,State::Black));
    std::set<std::pair<int,int>> pawns = model.checkRowSideBySidePawn();
    assert(pawns.empty());
}

void TestModel::should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;
    model.initGrid(size);
    assert(model.putInGrid(0,4,State::White));
    assert(model.putInGrid(1,4,State::White));
    assert(model.putInGrid(2,4,State::White));
    std::set<std::pair<int,int>> pawns;
    pawns.insert(std::make_pair(0,4));
    pawns.insert(std::make_pair(1,4));
    pawns.insert(std::make_pair(2,4));

    assert(model.checkColumnSideBySidePawn() == pawns);
}

void TestModel::should_return_empty_set_when_pawns_are_correctly_set_in_column()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,4,State::White));
    assert(model.putInGrid(1,4,State::White));
    std::set<std::pair<int,int>> pawns = model.checkColumnSideBySidePawn();
    assert(pawns.empty());
}

void TestModel::should_return_empty_set_when_testing_columns_with_pawns_set_in_row()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,4,State::White));
    assert(model.putInGrid(0,5,State::White));

    std::set<std::pair<int,int>> pawns = model.checkColumnSideBySidePawn();
    assert(pawns.empty());
}

void TestModel::should_return_empty_set_when_all_rows_are_balanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(0,4,State::White));
    assert(model.putInGrid(1,4,State::Black));
    assert(model.putInGrid(1,5,State::White));

    std::set<int> Rows = model.findUnbalancedRows();
    assert(Rows.empty());

}

void TestModel::should_return_rows_when_they_are_unbalanced()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::White));
    assert(model.putInGrid(2,2,State::Black));

    std::set<int> Rows;
    Rows.insert(0);
    Rows.insert(2);

    assert(model.findUnbalancedRows() == Rows);
}

void TestModel::should_return_empty_set_when_all_columns_are_balanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,1,State::White));
    assert(model.putInGrid(1,1,State::Black));
    assert(model.putInGrid(3,4,State::Black));
    assert(model.putInGrid(4,4,State::White));
    std::set<int> Rows = model.findUnbalancedColumns();
    assert(Rows.empty());
}

void TestModel::should_return_column_when_it_is_unbalanced()
{
    ModelTakuzu model(nullptr);
    int size = 6 ;

    model.initGrid(size);
    assert(model.putInGrid(0,1,State::White));
    assert(model.putInGrid(1,1,State::Black));
    assert(model.putInGrid(3,4,State::Black));
    assert(model.putInGrid(4,4,State::Black));
    std::set<int> Rows;
    Rows.insert(4);
    assert(model.findUnbalancedColumns() == Rows);
}

void TestModel::should_return_empty_set_when_all_columns_are_unique()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::White));
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(1,0,State::Black));
    assert(model.putInGrid(1,1,State::White));
    std::set<std::pair<int,int>> columns = model.findIdenticalRows();
    assert(columns.empty());
}

void TestModel::should_return_empty_set_when_columns_are_unique_but_rows_not()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::White));
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(0,2,State::White));
    assert(model.putInGrid(1,0,State::Black));
    assert(model.putInGrid(1,1,State::White));
    assert(model.putInGrid(1,2,State::White));
    assert(model.putInGrid(2,0,State::Black));
    assert(model.putInGrid(2,1,State::White));
    assert(model.putInGrid(2,2,State::White));
    std::set<std::pair<int,int>> columns = model.findIdenticalColumns();
    assert(columns.empty());
}

void TestModel::should_return_faulty_column_when_uniqueness_is_not_respected()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::White));
    assert(model.putInGrid(0,1,State::White));
    assert(model.putInGrid(0,2,State::White));

    assert(model.putInGrid(1,0,State::Black));
    assert(model.putInGrid(1,1,State::Black));
    assert(model.putInGrid(1,2,State::Black));

    std::set<std::pair<int,int>> wrongColumn;
    wrongColumn.insert(std::make_pair(0,1));
    wrongColumn.insert(std::make_pair(1,2));
    assert(model.findIdenticalColumns() == wrongColumn);
}

void TestModel::should_return_empty_set_when_all_rows_are_unique()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::White));
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(1,0,State::Black));
    assert(model.putInGrid(1,1,State::White));
    std::set<std::pair<int,int>> Row = model.findIdenticalRows();
    assert(Row.empty());
}

void TestModel::should_return_empty_set_when_rows_are_correct_but_columns_not()
{
    ModelTakuzu model(nullptr);
    int size = 3 ;

    model.initGrid(size);
    assert(model.putInGrid(0,0,State::Black));
    assert(model.putInGrid(0,1,State::White));
    assert(model.putInGrid(0,2,State::White));
    assert(model.putInGrid(1,0,State::White));
    assert(model.putInGrid(1,1,State::Black));
    assert(model.putInGrid(1,2,State::Black));
    assert(model.putInGrid(2,0,State::White));
    assert(model.putInGrid(2,1,State::White));
    assert(model.putInGrid(2,2,State::White));
    std::set<std::pair<int,int>> Row = model.findIdenticalRows();
    assert(Row.empty());
}

void TestModel::should_return_faulty_row_when_uniqueness_is_not_respected()
{
    ModelTakuzu model(nullptr);
    int size = 2 ;
    model.initGrid(size);
    assert(model.putInGrid(0,0,State::Black));
    assert(model.putInGrid(0,1,State::Black));
    assert(model.putInGrid(1,0,State::Black));
    assert(model.putInGrid(1,1,State::Black));
    std::set<std::pair<int,int>> Row;
    Row.insert(std::make_pair(0,1));
    assert(model.findIdenticalRows() == Row);
}

void TestModel::should_return_true_when_grid_is_correctly_finished()
{
    ModelTakuzu model(nullptr);
    int size = 2;
    model.initGrid(size);
    assert(model.putInGrid(0,0,State::Black));
    assert(model.putInGrid(0,1,State::White));

    assert(model.putInGrid(1,0,State::White));
    assert(model.putInGrid(1,1,State::Black));

    model.initColoredPawnNumber();
    assert(model.isGameFinished());
}


