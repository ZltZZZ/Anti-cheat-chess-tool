#include "new_anal_window.h"
#include "ui_new_anal_window.h"
#include <QFileDialog>
#include <QDir>
#include <string.h>
#include <QMessageBox>
#include <QValidator>

New_anal_window::New_anal_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_anal_window)
{
    ui->setupUi(this);
    connect(this, &New_anal_window::new_analysis_initialization_finished, this->main_w_ptr, &MainWindow::start_analyze);
}

New_anal_window::~New_anal_window()
{
    delete ui;
}

void New_anal_window::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "PGN (*.pgn)");
    ui->pathDB->setText(fileName);
}


void New_anal_window::on_minRUse_clicked()
{
    ui->minR->setReadOnly(false);
    ui->minR->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->minR->setValidator( new QIntValidator(1, 9999, this) );
}


void New_anal_window::on_minRDontUse_clicked()
{
    ui->minR->setReadOnly(true);
    ui->minR->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_maxRDontUse_clicked()
{
    ui->maxR->setReadOnly(true);
    ui->maxR->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_maxRUse_clicked()
{
    ui->maxR->setReadOnly(false);
    ui->maxR->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->maxR->setValidator( new QIntValidator(1, 9999, this) );
}


void New_anal_window::on_countMovesUse_clicked()
{
    ui->countMoves->setReadOnly(false);
    ui->countMoves->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->countMoves->setValidator( new QIntValidator(0, 9999999, this) );
}


void New_anal_window::on_countMovesDontUse_clicked()
{
    ui->countMoves->setReadOnly(true);
    ui->countMoves->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countGamesUse_clicked()
{
    ui->countGames->setReadOnly(false);
    ui->countGames->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->countGames->setValidator( new QIntValidator(0, 9999999, this) );
}


void New_anal_window::on_countGamesDontUse_clicked()
{
    ui->countGames->setReadOnly(true);
    ui->countGames->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "Engine (*.exe)");
    ui->pathEngine->setText(fileName);
}


void New_anal_window::on_countLinesCustom_clicked()
{
    ui->countLines->setReadOnly(false);
    ui->countLines->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->countLines->setValidator( new QIntValidator(0, 99, this) );
}


void New_anal_window::on_hashSizeCustom_clicked()
{
    ui->hashSize->setReadOnly(false);
    ui->hashSize->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->hashSize->setValidator( new QIntValidator(0, 9999999, this) );
}


void New_anal_window::on_moveTimeCustom_clicked()
{
    ui->moveTime->setReadOnly(false);
    ui->moveTime->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->moveTime->setValidator( new QIntValidator(0, 9999999, this) );
}


void New_anal_window::on_countCPUDef_clicked()
{
    ui->countCpu->setReadOnly(true);
    ui->countCpu->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countLinesDef_clicked()
{
    ui->countLines->setReadOnly(true);
    ui->countLines->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_hashSizeDef_clicked()
{
    ui->hashSize->setReadOnly(true);
    ui->hashSize->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_moveTimeDef_clicked()
{
    ui->moveTime->setReadOnly(true);
    ui->moveTime->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countCPUCustom_clicked()
{
    ui->countCpu->setReadOnly(false);
    ui->countCpu->setStyleSheet("background-color: rgb(255, 255, 255)");
    ui->countCpu->setValidator( new QIntValidator(0, 9999999, this) );
}

wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}

bool New_anal_window::check_param_fields(){
    if (
        ui->pathDB->text().isEmpty() ||
        ui->nameSusp->text().isEmpty() ||
        (ui->minRUse->isChecked() && ui->minR->text().isEmpty()) ||
        (ui->maxRUse->isChecked() && ui->maxR->text().isEmpty()) ||
        (ui->countMovesUse->isChecked() && ui->countMoves->text().isEmpty()) ||
        (ui->countGamesUse->isChecked() && ui->countGames->text().isEmpty()) ||
        ui->pathEngine->text().isEmpty() ||
        (ui->countCPUCustom->isChecked() && ui->countCpu->text().isEmpty()) ||
        (ui->countLinesCustom->isChecked() && ui->countLines->text().isEmpty()) ||
        (ui->hashSizeCustom->isChecked() && ui->hashSize->text().isEmpty()) ||
        (ui->moveTimeCustom->isChecked() && ui->moveTime->text().isEmpty())
        ){
        QMessageBox::critical(this, "Error", "Please, fill all text fields.");
        return false;
    }else if (atoi(ui->minR->text().toStdString().c_str()) > atoi(ui->maxR->text().toStdString().c_str())){
        QMessageBox::critical(this, "Error", "Min rating must be lower or equal to max rating.");
        return false;
    }
    else{
        if (engine_load(&this->main_w_ptr->engn) == ENGINE_LOAD_OK){
            engine_close(&this->main_w_ptr->engn);
        }else{
            QMessageBox::critical(this, "Error", "Incorrect engine.");
            return false;
        }

        return true;
    }
}

void New_anal_window::on_StartAnalButt_clicked()
{
    wchar_t* engn_path_w = NULL;

    /* Init engine struct. */

    // Set engine path
    engn_path_w = GetWC(ui->pathEngine->text().toStdString().c_str());
    init_engine_struct(&this->main_w_ptr->engn, engn_path_w);

    // Set engine CPU
    if (ui->countCPUCustom->isChecked()) {
        this->main_w_ptr->engn.cpu = atoi(ui->countCpu->text().toStdString().c_str());
    }

    // Set engine lines
    if (ui->countLinesCustom->isChecked()) {
        this->main_w_ptr->engn.multi_pv = atoi(ui->countLines->text().toStdString().c_str());
    }

    // Set engine hash
    if (ui->hashSizeCustom->isChecked()) {
        this->main_w_ptr->engn.hash = atoi(ui->hashSize->text().toStdString().c_str());
    }

    // Set engine movetime
    if (ui->moveTimeCustom->isChecked()) {
        this->main_w_ptr->engn.move_time = atoi(ui->moveTime->text().toStdString().c_str());
    }

    /* Set parser parametrs. */
    init_parser(&this->main_w_ptr->prsr);

    // Set parser dbPath
    memcpy(this->main_w_ptr->prsr.db.path_to_db, ui->pathDB->text().toStdString().c_str(), MAX_PATH_LENTH);

    // Set parser nameSusp
    memcpy(this->main_w_ptr->prsr.fiter.name, ui->nameSusp->text().toStdString().c_str(), MAX_NAME_SIZE);

    // Set parser typeOfGames
    if (ui->blitz->isChecked()){
        this->main_w_ptr->prsr.fiter.evnt = EVENT_BLITZ;
    }else if (ui->bullet->isChecked()){
        this->main_w_ptr->prsr.fiter.evnt = EVENT_BULLET;
    }else{
        this->main_w_ptr->prsr.fiter.evnt = EVENT_CLASSIC;
    }

    // Set parser min/max rating
    if (ui->maxRUse->isChecked()){
        this->main_w_ptr->prsr.fiter.elo_max = atoi(ui->maxR->text().toStdString().c_str());
    }
    if (ui->minRUse->isChecked()){
        this->main_w_ptr->prsr.fiter.elo_min = atoi(ui->minR->text().toStdString().c_str());
    }

    // Set parser maxCountMoves
    if (ui->countMovesUse->isChecked()){
        this->main_w_ptr->prsr.fiter.max_count_of_moves = atoi(ui->countMoves->text().toStdString().c_str());
    }

    // Set parser maxCountGames
    if (ui->countGamesUse->isChecked()){
        this->main_w_ptr->prsr.fiter.max_count_of_games = atoi(ui->countGames->text().toStdString().c_str());
    }

    /* Init suspect portrait structs. */
    init_suspect_portrait(&this->main_w_ptr->player, &this->main_w_ptr->prsr);
    init_suspect_portrait(&this->main_w_ptr->same_rating, &this->main_w_ptr->prsr);

    if (this->check_param_fields()){
        // Start analysis
        emit new_analysis_initialization_finished();
        close();
    }
}

void New_anal_window::new_analysis_initialization_finished()
{

}

