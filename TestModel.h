#ifndef TESTMODEL_H
#define TESTMODEL_H


class TestModel
{
public:
    TestModel();
private:

    void should_return_true_when_put_pawn_in_boundary();
    void should_return_false_when_put_pawn_out_out_of_bounds();

    void should_return_position_of_faulty_pawns_when_3pawns_are_side_by_side_in_rows();
    void should_return_empty_set_when_pawns_are_correctly_set_in_row();
    void should_return_empty_set_when_testing_rows_with_pawns_set_in_column();
    void should_return_empty_set_when_pawn_between_pawns_of_different_colors();

    void should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();
    void should_return_empty_set_when_pawns_are_correctly_set_in_column();
    void should_return_empty_set_when_testing_columns_with_pawns_set_in_row();

    void should_return_empty_set_when_all_rows_are_balanced();
    void should_return_rows_when_they_are_unbalanced();

    void should_return_empty_set_when_all_columns_are_balanced();
    void should_return_column_when_it_is_unbalanced();


    void should_return_empty_set_when_all_columns_are_unique();
    void should_return_empty_set_when_columns_are_unique_but_rows_not();
    void should_return_faulty_column_when_uniqueness_is_not_respected();

    void should_return_empty_set_when_all_rows_are_unique();
    void should_return_empty_set_when_rows_are_correct_but_columns_not();
    void should_return_faulty_row_when_uniqueness_is_not_respected();


};

#endif // TESTMODEL_H
