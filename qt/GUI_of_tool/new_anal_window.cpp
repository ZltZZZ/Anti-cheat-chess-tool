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


void set_unactive(QLineEdit* line){
    line->setText("");
    line->setReadOnly(true);
    line->setStyleSheet("background-color: rgb(240, 240, 240)");
}
void set_active(QLineEdit* line, New_anal_window* wind){
    line->setText("");
    line->setReadOnly(false);
    line->setStyleSheet("background-color: rgb(255, 255, 255)");
    line->setValidator( new QIntValidator(1, 999999999, wind) );
}

void New_anal_window::on_minRUse_clicked()
{
    set_active(ui->minR, this);
}


void New_anal_window::on_minRDontUse_clicked()
{
    set_unactive(ui->minR);
}


void New_anal_window::on_maxRDontUse_clicked()
{
    set_unactive(ui->maxR);
}


void New_anal_window::on_maxRUse_clicked()
{
    set_active(ui->maxR, this);
}


void New_anal_window::on_countMovesUse_clicked()
{
    set_active(ui->countMoves, this);
}


void New_anal_window::on_countMovesDontUse_clicked()
{
    set_unactive(ui->countMoves);
}


void New_anal_window::on_countGamesUse_clicked()
{
    set_active(ui->countGames, this);
}


void New_anal_window::on_countGamesDontUse_clicked()
{
    set_unactive(ui->countGames);
}


void New_anal_window::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "Engine (*.exe)");
    ui->pathEngine->setText(fileName);
}


void New_anal_window::on_countLinesCustom_clicked()
{
    set_active(ui->countLines, this);
}


void New_anal_window::on_hashSizeCustom_clicked()
{
    set_active(ui->hashSize, this);
}


void New_anal_window::on_moveTimeCustom_clicked()
{
    set_active(ui->moveTime, this);
}


void New_anal_window::on_countCPUDef_clicked()
{
    set_unactive(ui->countCpu);
}


void New_anal_window::on_countLinesDef_clicked()
{
    set_unactive(ui->countLines);
}


void New_anal_window::on_hashSizeDef_clicked()
{
    set_unactive(ui->hashSize);
}


void New_anal_window::on_moveTimeDef_clicked()
{
    set_unactive(ui->moveTime);
}


void New_anal_window::on_countCPUCustom_clicked()
{
    set_active(ui->countCpu, this);
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
        FILE* testfile = NULL;

        if (engine_load(&this->engn) == ENGINE_LOAD_OK){
            engine_close(&this->engn);
        }else{
            QMessageBox::critical(this, "Error", "Incorrect engine.");
            return false;
        }

        if (!fopen_s(&testfile, this->prsr.db.path_to_db, "r")){
            fclose(testfile);
        }else{
            QMessageBox::critical(this, "Error", "Incorrect database (.pgn) file.");
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
    init_engine_struct(&this->engn, engn_path_w);

    // Set engine CPU
    if (ui->countCPUCustom->isChecked()) {
        this->engn.cpu = atoi(ui->countCpu->text().toStdString().c_str());
    }

    // Set engine lines
    if (ui->countLinesCustom->isChecked()) {
        this->engn.multi_pv = atoi(ui->countLines->text().toStdString().c_str());
    }

    // Set engine hash
    if (ui->hashSizeCustom->isChecked()) {
        this->engn.hash = atoi(ui->hashSize->text().toStdString().c_str());
    }

    // Set engine movetime
    if (ui->moveTimeCustom->isChecked()) {
        this->engn.move_time = atoi(ui->moveTime->text().toStdString().c_str());
    }

    /* Set parser parametrs. */
    init_parser(&this->prsr);

    // Set parser dbPath
    memcpy(this->prsr.db.path_to_db, ui->pathDB->text().toStdString().c_str(), MAX_PATH_LENTH);

    // Set parser nameSusp
    memcpy(this->prsr.fiter.name, ui->nameSusp->text().toStdString().c_str(), MAX_NAME_SIZE);

    // Set parser typeOfGames
    if (ui->blitz->isChecked()){
        this->prsr.fiter.evnt = EVENT_BLITZ;
    }else if (ui->bullet->isChecked()){
        this->prsr.fiter.evnt = EVENT_BULLET;
    }else{
        this->prsr.fiter.evnt = EVENT_CLASSIC;
    }

    // Set parser min/max rating
    if (ui->maxRUse->isChecked()){
        this->prsr.fiter.elo_max = atoi(ui->maxR->text().toStdString().c_str());
    }
    if (ui->minRUse->isChecked()){
        this->prsr.fiter.elo_min = atoi(ui->minR->text().toStdString().c_str());
    }

    // Set parser maxCountMoves
    if (ui->countMovesUse->isChecked()){
        this->prsr.fiter.max_count_of_moves = atoi(ui->countMoves->text().toStdString().c_str());
    }

    // Set parser maxCountGames
    if (ui->countGamesUse->isChecked()){
        this->prsr.fiter.max_count_of_games = atoi(ui->countGames->text().toStdString().c_str());
    }

    /* Init suspect portrait structs. */
    init_suspect_portrait(&this->player, &this->prsr);
    init_suspect_portrait(&this->db, &this->prsr);

    if (this->check_param_fields()){
        // Start analysis
        this->main_w_ptr->start_analyze(&prsr, &engn, &player, &db);
        close();
    }
}

void New_anal_window::closeW()
{
    close();
}



void New_anal_window::on_saveConfButt_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save configuration", QDir::homePath(), "Analysis config (*.aconf)");
    FILE* confFile = NULL;

    fopen_s(&confFile, fileName.toStdString().c_str(), "w");
    if (confFile == NULL){
        QMessageBox::critical(this, "Error", "Incorrect name or path, please try again");
    }else{
        fprintf(confFile, "%s\n", ui->pathDB->text().toStdString().c_str());
        fprintf(confFile, "%s\n", ui->nameSusp->text().toStdString().c_str());
        if (ui->bullet->isChecked()){
            fprintf(confFile, "bullet\n");
        }else if (ui->blitz->isChecked()){
            fprintf(confFile, "blitz\n");
        }else{
            fprintf(confFile, "classic\n");
        }
        if (ui->minRDontUse->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->minR->text().toStdString().c_str());
        if (ui->maxRDontUse->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->maxR->text().toStdString().c_str());
        if (ui->countMovesDontUse->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->countMoves->text().toStdString().c_str());
        if (ui->countGamesDontUse->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->countGames->text().toStdString().c_str());
        fprintf(confFile, "%s\n", ui->pathEngine->text().toStdString().c_str());
        if (ui->countCPUDef->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->countCpu->text().toStdString().c_str());
        if (ui->countLinesDef->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->countLines->text().toStdString().c_str());
        if (ui->hashSizeDef->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->hashSize->text().toStdString().c_str());
        if (ui->moveTimeDef->isChecked()) fprintf(confFile, "no\n"); else fprintf(confFile, "%s\n", ui->moveTime->text().toStdString().c_str());

        fclose(confFile);
    }
}


void New_anal_window::on_loadConfButt_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose configuration", QDir::homePath(), "Analysis config (*.aconf)");
    FILE* confFile = NULL;

    fopen_s(&confFile, fileName.toStdString().c_str(), "r");
    if (confFile == NULL){
        QMessageBox::critical(this, "Error", "Can't open configuration file, please try again");
    }else{
        char buff[500] = {'\0'};
        char c;
        int i = 0;

        while(!feof(confFile)){
            memset(buff, '\0', sizeof(char) * 500);
            fscanf_s(confFile, "%[^\n]%c", buff, 500, &c, 1);
            i++;

            switch (i) {
            case 1:
                ui->pathDB->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                break;
            case 2:
                ui->nameSusp->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                break;
            case 3:
                if (!strcmp(buff, "blitz")){
                    ui->blitz->setChecked(true);
                }else if (!strcmp(buff, "bullet")){
                    ui->bullet->setChecked(true);
                }else{
                    ui->classic->setChecked(true);
                }
                break;
            case 4:
                if (!strcmp(buff, "no")){
                    ui->minRDontUse->setChecked(true);
                    set_unactive(ui->minR);
                }else{
                    ui->minRUse->setChecked(true);
                    set_active(ui->minR, this);
                    ui->minR->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 5:
                if (!strcmp(buff, "no")){
                    ui->maxRDontUse->setChecked(true);
                    set_unactive(ui->maxR);
                }else{
                    ui->maxRUse->setChecked(true);
                    set_active(ui->maxR, this);
                    ui->maxR->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 6:
                if (!strcmp(buff, "no")){
                    ui->countMovesDontUse->setChecked(true);
                    set_unactive(ui->countMoves);
                }else{
                    ui->countMovesUse->setChecked(true);
                    set_active(ui->countMoves, this);
                    ui->countMoves->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 7:
                if (!strcmp(buff, "no")){
                    ui->countGamesDontUse->setChecked(true);
                    set_unactive(ui->countGames);
                }else{
                    ui->countGamesUse->setChecked(true);
                    set_active(ui->countGames, this);
                    ui->countGames->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 8:
                ui->pathEngine->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                break;
            case 9:
                if (!strcmp(buff, "no")){
                    ui->countCPUDef->setChecked(true);
                    set_unactive(ui->countCpu);
                }else{
                    ui->countCPUCustom->setChecked(true);
                    set_active(ui->countCpu, this);
                    ui->countCpu->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 10:
                if (!strcmp(buff, "no")){
                    ui->countLinesDef->setChecked(true);
                    set_unactive(ui->countLines);
                }else{
                    ui->countLinesCustom->setChecked(true);
                    set_active(ui->countLines, this);
                    ui->countLines->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 11:
                if (!strcmp(buff, "no")){
                    ui->hashSizeDef->setChecked(true);
                    set_unactive(ui->hashSize);
                }else{
                    ui->hashSizeCustom->setChecked(true);
                    set_active(ui->hashSize, this);
                    ui->hashSize->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            case 12:
                if (!strcmp(buff, "no")){
                    ui->moveTimeDef->setChecked(true);
                    set_unactive(ui->moveTime);
                }else{
                    ui->moveTimeCustom->setChecked(true);
                    set_active(ui->moveTime, this);
                    ui->moveTime->setText(QString::fromLocal8Bit(buff, strlen(buff)));
                }
                break;
            default:
                break;
            }
        }

        fclose(confFile);
    }
}

