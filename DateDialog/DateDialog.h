#ifndef DATE_DIALOG_H
#define DATE_DIALOG_H
#include <QDialog>
#include <QDialogButtonBox>
#include <QDateEdit>
#include <QLabel>

class DateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DateDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~DateDialog();
    void setText(const QString& value);
    QDate getDate();
private:
    QLabel* label;
    QDateEdit* dateEdit;
    QDialogButtonBox* buttonBox;
};

#endif