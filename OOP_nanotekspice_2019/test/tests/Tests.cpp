/*
** EPITECH PROJECT, 2019
** CPP_piscine
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include "Pin.hpp"

/*
static void redir_strout()
{
    cr_redirect_stdout();
}

static void redir_sterr()
{
    cr_redirect_stderr();
}
*/

/* ----TESTS---- */

Test(SubjectToTest, specificThingOfThisSubject)
{
    cr_assert_neq(false, true);

    cr_assert_eq(10, 10);
    cr_assert_eq(false, false);
    cr_assert_eq(10, 10);
}

Test(Pins, 0ArgPinCreation)
{
    nts::Pin pin;
    nts::Pin pinCompare(nts::Pin::PinType::ELECTRICAL, nts::Tristate::UNDEFINED);

    cr_assert_eq(pin, pinCompare);
}

Test(Pins, 1ArgPinCreation)
{
    nts::Pin pinCompare;
    nts::Pin pinOutput(nts::Pin::OUTPUT);
    nts::Pin pinInput(nts::Pin::INPUT);
    nts::Pin pinElectrical(nts::Pin::ELECTRICAL);

    cr_assert_neq(pinOutput, pinCompare);
    cr_assert_neq(pinInput, pinCompare);
    cr_assert_eq(pinElectrical, pinCompare);
}

Test(Pins, 2ArgPinCreation)
{
    nts::Pin pinCompare;
    nts::Pin pinInputTrue(nts::Pin::INPUT, nts::Tristate::TRUE);
    nts::Pin pinElecUn(nts::Pin::ELECTRICAL, nts::Tristate::UNDEFINED);

    cr_assert_neq(pinInputTrue.getState(), pinCompare.getState());
    cr_assert_neq(pinInputTrue.getType(), pinCompare.getType());

    cr_assert_eq(pinElecUn.getState(), pinCompare.getState());
    cr_assert_eq(pinElecUn.getType(), pinCompare.getType());
}