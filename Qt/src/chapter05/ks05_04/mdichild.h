/*! 
* Copyright (C) 2018 女儿叫老白
* 版权所有。
* 代码仅用于课程《Qt入门与提高-GUI产品开发》的学习，请勿传播。
* 免责声明:代码不保证稳定性，请勿用作商业用途，否则后果自负。

\file: mdichild.h
\brief  MdiChild 类的定义文件

\author 女儿叫老白  星点分享: http://xingdianketang.cn/
\Date 2018/9
*/


#ifndef MDICHILD_H
#define MDICHILD_H

#include <QTextEdit>

class MdiChild : public QTextEdit
{
    Q_OBJECT

public:
    MdiChild();

    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile() { return curFile; }

Q_SIGNALS:
	void textSelected(const QString&); // xingdianketang

protected:
    void closeEvent(QCloseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *e) override; // xingdianketang

private slots:
    void documentWasModified();
private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

    QString curFile;
    bool isUntitled;
};

#endif
