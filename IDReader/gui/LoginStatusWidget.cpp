#include "LoginStatusWidget.h"
#include "ui_LoginStatusWidget.h"
#include "bean/Student.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>

LoginStatusWidget::LoginStatusWidget(QWidget *parent) : QWidget(parent), ui(new Ui::LoginStatusWidget) {
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true); // 启用 QSS

    model = new QStandardItemModel();

    ui->listView->setModel(model);
    ui->listView->setWrapping(true); // 空间不够显示后自动折叠
    ui->listView->setFlow(QListView::LeftToRight); // 从左向右排列
    ui->listView->setViewMode(QListView::IconMode); // 文字在图标下面
    ui->listView->setResizeMode(QListView::Adjust); // 大小变化后重新布局 items
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不允许编辑
    ui->listView->setIconSize(QSize(64, 64)); // 图标大小
}

LoginStatusWidget::~LoginStatusWidget() {
    delete ui;
}

void LoginStatusWidget::setStudents(const QList<Student> &students) {
    model->clear();

    QIcon onlineIcon(":/icon/online.png");
    QIcon offlineIcon(":/icon/offline.png");

    // for (int i = 0; i < 50; ++i) // 测试滚动条
    foreach (const Student &student, students) {
        QStandardItem *item = new QStandardItem(student.signedAt.isEmpty() ? offlineIcon : onlineIcon, student.examineeName);
        QString toolTip = QString("姓名: %1<br>准考证号: %2<br>身份证号: %3<br>签到时间: %4")
                .arg(student.examineeName).arg(student.examUid).arg(student.idCardNo).arg(student.signedAt);
        item->setToolTip(toolTip);

        model->appendRow(item);
    }
}