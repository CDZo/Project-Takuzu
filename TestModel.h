#ifndef TESTMODEL_H
#define TESTMODEL_H


class TestModel
{
public:
    TestModel();
private:
    void should_return_faulty_lign_when_3pawns_are_side_by_side_in_ligns();
    void should_return_gridsize_when_pawns_are_correctly_set_in_lign();
    void should_return_gridsize_when_testing_ligns_with_pawns_set_in_column();

    void should_return_faulty_columns_when_3pawns_are_side_by_side_in_columns();
    void should_return_gridsize_when_pawns_are_correctly_set_in_column();
    void should_return_gridsize_when_testing_coliumns_with_pawns_set_in_lign();
};

#endif // TESTMODEL_H