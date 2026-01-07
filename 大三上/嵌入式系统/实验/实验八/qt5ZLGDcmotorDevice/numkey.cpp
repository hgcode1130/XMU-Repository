#include \
numkey.h\

numKey::numKey(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout(this);
    // Create keys 0-9
    for(int i = 0; i <= 9; ++i) {
        buttons[i] = new QPushButton(QString::number(i), this);
        buttons[i]->setFixedSize(60, 60);
        buttons[i]->setStyleSheet(\QPushButton
font:bold 20px;
\);
    }
    
    // Layout 1-9
    int r=0, c=0;
    for(int i=1; i<=9; ++i) {
        layout->addWidget(buttons[i], r, c);
        c++;
        if(c > 2) { c=0; r++; }
    }
    // 0 uses a specific spot
    layout->addWidget(buttons[0], 3, 1);
}

QPushButton* numKey::getButton(int index)
{
    if (index >= 0 && index < 10)
        return buttons[index];
    return nullptr;
}
