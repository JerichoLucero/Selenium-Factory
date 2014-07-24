/*
 * Author: Austin Walters
 * Last Modified: July 23, 2014
 * Project: Selenium Factory
 */

#include "testgenerationform.h"
#include "ui_testgenerationform.h"

testGenerationForm::testGenerationForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::testGenerationForm){
        ui->setupUi(this);

        QDir dir;
        while(!dir.cd("scripts")){ dir.cdUp(); }
        parse browserOSOpts(dir.absolutePath().toStdString() + "/BrowserOS.csv");
        opts = browserOSOpts.getVector();
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
    this->selectedOptions();
    this->hide();
}

/**
 * @brief testGenerationForm::on_cencelButton_clicked
 *      Returns every value in the test genearation
 *      form to the default state.
 */
void testGenerationForm::on_cencelButton_clicked(){

    ui->chromeSlider->setValue(0);
    ui->firefoxSlider->setValue(0);

    ui->windowsCheckBox->setChecked(false);
    ui->macCheckBox->setChecked(false);
    ui->linuxCheckBox->setChecked(false);

    ui->chromeCheckBox->setChecked(false);
    ui->firefoxCheckBox->setChecked(false);
    ui->safariCheckBox->setChecked(false);
    ui->operaCheckBox->setChecked(false);
    ui->IECheckBox->setChecked(false);
    ui->defaultBrowserCheckBox->setChecked(false);

    ui->deviceBox->setChecked(false);

    ui->testSuiteCheckBox->setChecked(false);
    ui->testNameEdit->setText("Specific Test Name");
    ui->testSuiteEdit->setText("New Test Suite");

    this->hide();
}

/**
 * @brief Slider Value
 *
 *          The functions below are going to have various implications.
 *
 *          For example, on slidebarChrome = 99, the chrome browser versions
 *          should be tested maximally for what ever operating platforms chosen.
 *
 *          If on the other hand, slidebarChrome = 55, half the chrome browser
 *          versions should be tested on the various OS versions.
 *
 */

void testGenerationForm::on_chromeSlider_valueChanged(int value){
    int version = double(value) / double(99.0 / 9.0);
    version += 1;
    ui->chromeCheckBox->setText("Chrome " + QString::number(version));
    ui->chromeCheckBox->setChecked(true);
}

/**
 * @brief testGenerationForm::on_firefoxSlider_valueChanged
 *            Changes the versions tested on FireFox,
 *              from most recent to least recent post.
 * @param value
 */
void testGenerationForm::on_firefoxSlider_valueChanged(int value){
    int version = double(value) / double(99.0 / 25.0);
    version += 1;
    ui->firefoxCheckBox->setText("FireFox:  " + QString::number(version));
    ui->firefoxCheckBox->setChecked(true);
}

/**
 * @brief testGenerationForm::selectedOptions
 *
 *          Returns the selected options in the following form:
 *
 *          Platform, Browser, Browser Version, Device (nil if none);
 *
 *          Each string of options will be broken up by a semicolon, and the device
 *          category will be nil if no device was selected.
 */
std::string testGenerationForm::selectedOptions(){
    std::string options = "";

    if(ui->androidCheckBox->isChecked())
       options += addAndroid(options);
    if(ui->iosCheckBox->isChecked())
        options += addiOS(options);
    if(ui->windowsCheckBox->isChecked())
        options += addWindows(options);
    if(ui->macCheckBox->isChecked())
        options += addMac(options);
    if(ui->linuxCheckBox->isChecked())
        options += addLinux(options);

    // For testing only
    std::cout << "----- Options -----\n\n";
    std::cout << options << std::endl;

    return options;
}

std::string testGenerationForm::addAndroid(std::string options){
    for(unsigned int i = 0; i < opts.size(); i++){
        if(0 == std::strcmp(opts[i][1].c_str(), "Android")
        || 0 == std::strcmp(opts[i][1].c_str(), "android")){
            options += addOSBrowser(i);
        }
    }
    return options;
}

std::string testGenerationForm::addiOS(std::string options){
    for(unsigned int i = 0; i < opts.size(); i++){
        if(0 == std::strcmp(opts[i][1].c_str(), "iPad")
        || 0 == std::strcmp(opts[i][1].c_str(), "iPhone")){
            options += addOSBrowser(i);
        }
    }
    return options;
}

std::string testGenerationForm::addWindows(std::string options){
    for(unsigned int i = 0; i < opts.size(); i++){
        if(0 == strncmp(opts[i][0].c_str(), "Windows", 7)
        || 0 == strncmp(opts[i][0].c_str(), "windows", 7)){
            options += addOSBrowser(i);
        }
    }
    return options;
}

std::string testGenerationForm::addMac(std::string options){
    for(unsigned int i = 0; i < opts.size(); i++){
        if(0 == strncmp(opts[i][0].c_str(), "OS X", 4)
        || 0 == strncmp(opts[i][0].c_str(), "os x", 4)){
            options += addOSBrowser(i);
        }
    }
    return options;
}

std::string testGenerationForm::addLinux(std::string options){
    for(unsigned int i = 0; i < opts.size(); i++){
        if(0 == strncmp(opts[i][0].c_str(), "linux", 5)
        || 0 == strncmp(opts[i][0].c_str(), "Linux", 5)){
            options += addOSBrowser(i);
        }
    }
    return options;
}

std::string testGenerationForm::addMobile(int index){

    std::string line = opts[index][0] + "," + opts[index][1] + ",";

    if(ui->androidEmulatedBox->isChecked() &&
      (0 == std::strcmp(opts[index][3].c_str(), "Android"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->HTCOneXBox->isChecked() &&
      (0 == std::strcmp(opts[index][3].c_str(), "HTC One X"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->samsungGalaxyNexusBox->isChecked() &&
      (0 == std::strcmp(opts[index][3].c_str(), "Samsung Galaxy Nexus"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->googleNexus7CBox->isChecked() &&
      (0 == std::strcmp(opts[index][3].c_str(), "Google Nexus 7C"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->motorolaDroid4Box->isChecked() &&
      (0 == std::strcmp(opts[index][3].c_str(), "Motorola Droid 4"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->iPhoneBox->isChecked() &&
    (0 == std::strcmp(opts[index][3].c_str(), "iPhone"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }
    if(ui->iPadBox->isChecked() &&
    (0 == std::strcmp(opts[index][3].c_str(), "iPad"))){
        return line + opts[index][2] + "," + opts[index][3] + ";";
    }

    return "";
}

std::string testGenerationForm::addOSBrowser(int index){

    std::string line = opts[index][0] + "," + opts[index][1] + ",";

    bool firefox = (0 == std::strcmp(opts[index][1].c_str(), "FireFox")
            || 0 == std::strcmp(opts[index][1].c_str(), "firefox"));
    int firefoxV = double(99 - ui->firefoxSlider->value()) / double(99.0 / 26.0);
    firefoxV += 4;

    bool chrome = (0 == strcmp(opts[index][1].c_str(), "Chrome")
            || 0 == strcmp(opts[index][1].c_str(), "chrome"));
    int chromeV = double(99 - ui->chromeSlider->value()) / double(99.0 / 9.0);
    chromeV += 26;

    bool ie = (0 == strcmp(opts[index][1].c_str(), "IE")
            || 0 == strcmp(opts[index][1].c_str(), "ie"));

    bool safari = (0 == strcmp(opts[index][1].c_str(), "Safari")
            || 0 == strcmp(opts[index][1].c_str(), "Safari"));

    bool opera = (0 == strcmp(opts[index][1].c_str(), "Opera")
            || 0 == strcmp(opts[index][1].c_str(), "opera"));

    if(firefox && ui->firefoxCheckBox->isChecked()){
        if(std::atoi(opts[index][2].c_str()) > firefoxV)
            return line + opts[index][2] + ";";
    }

    if(chrome && ui->chromeCheckBox->isChecked()){
        if(std::atoi(opts[index][2].c_str()) > chromeV)
            return line + opts[index][2] + ";";
    }

    if((ui->IECheckBox->isChecked() && ie)
    || (ui->safariCheckBox->isChecked() && safari)
    || (ui->operaCheckBox->isChecked() && opera)){
        return line + opts[index][2] + ";";
    }

    if(ui->androidCheckBox->isChecked()
    || ui->iosCheckBox->isChecked()){
        return addMobile(index);
    }

    return "";
}

void testGenerationForm::on_testNameEdit_returnPressed(){
    bool ok;
    funcDescription = QInputDialog::getText(this, tr("Function Description"),
                                             tr("Function Description"), QLineEdit::Normal,
                                             "Description of Function", &ok).toStdString();
}

/**
 * @brief Below are a large number of "checked" functions,
 *        if a checkbox is checked, these functions will be used
 *        to check the "heirarchy" boxes, such as "android or iOS.
 */
void testGenerationForm::on_HTCOneXBox_clicked(bool checked){

}

void testGenerationForm::on_androidEmulatedBox_clicked(bool checked){

}

void testGenerationForm::on_samsungGalaxyNexusBox_clicked(bool checked){

}

void testGenerationForm::on_googleNexus7CBox_clicked(bool checked){

}

void testGenerationForm::on_motorolaDroid4Box_clicked(bool checked){

}

void testGenerationForm::on_iPhoneBox_clicked(bool checked){

}

void testGenerationForm::on_iPadBox_clicked(bool checked){

}

void testGenerationForm::on_androidCheckBox_clicked(bool checked){

}

void testGenerationForm::on_iosCheckBox_clicked(bool checked){

}

void testGenerationForm::on_deviceBox_clicked(){

}
