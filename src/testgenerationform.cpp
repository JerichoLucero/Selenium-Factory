#include "testgenerationform.h"
#include "ui_testgenerationform.h"
#include <iostream>

testGenerationForm::testGenerationForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testGenerationForm){
    ui->setupUi(this);
}

testGenerationForm::~testGenerationForm(){
    delete ui;
}

/**
 * @brief testGenerationForm::on_buttonBox_accepted - Accepted the generation form.
 *          Should call various functions to check the checkboxes,
 *          then call a python script to check for specific functions using the API,
 *          then finally should check to see if function already exists in database.
 *
 *          If the function does not exist in the database, create the test and add it
 *          to the database, potentially also adding it to a test suite. Have them also
 *          add a brief description (perhaps tags?), for quick searches and easy (later)
 *          combination of tests to create suites.
 *
 *          If the function does exist in the database, inform the user, and also direct
 *          them to the test location. Hopefully, the database will be full of similar tests.
 *          As well as other tests they may run in the future, allowing them to save time.
 */
void testGenerationForm::on_acceptButton_clicked(){
    this->hide();
}

/**
 * @brief testGenerationForm::on_cencelButton_clicked
 *      Returns every value in the test genearation
 *      form to the default state.
 */
void testGenerationForm::on_cencelButton_clicked(){

    ui->chromeSlider->setValue(0);
    ui->defaultSlider->setValue(0);
    ui->firefoxSlider->setValue(0);
    ui->safariSlider->setValue(0);

    ui->androidCheckBox->setChecked(false);
    ui->iosCheckBox->setChecked(false);
    ui->windowsCheckBox->setChecked(false);
    ui->macCheckBox->setChecked(false);
    ui->linuxCheckBox->setChecked(false);

    ui->chromeCheckBox->setChecked(false);
    ui->firefoxCheckBox->setChecked(false);
    ui->safariCheckBox->setChecked(false);
    ui->operaCheckBox->setChecked(false);

    ui->deviceBox->setChecked(false);

    ui->testSuiteCheckBox->setChecked(false);
    ui->testNameEdit->setText("Specific Test Name");
    ui->testSuiteEdit->setText("New Test Suite");

    this->hide();
}

/**
 * @brief testGenerationForm::on_Slider_valueChanged
 *
 *          The functions below are going to have various implications.
 *
 *          For example, on slidebarChrome = 99, the chrome browser should
 *          be tested maximally for what ever operating platforms chosen.
 *
 *          If on the other hand, slidebarChrome = 55, the chrome browser should
 *          be tested based on the following formula:
 *
 *          sidebarChrome / < OS Version Count >
 *
 */
void testGenerationForm::on_defaultSlider_valueChanged(int value){

}

void testGenerationForm::on_firefoxSlider_valueChanged(int value){

}




