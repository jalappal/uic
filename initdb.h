#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QCoreApplication>

QVariant addEmployee(QSqlQuery &q, const QString &name, const QDate &birthdate, const QVariant &area,
                     const QString &phonenumber)
{
    q.addBindValue(name);
    q.addBindValue(birthdate);
    q.addBindValue(area);
    q.addBindValue(phonenumber);
    q.exec();
    return q.lastInsertId();
}

QVariant addSkill(QSqlQuery &q, const QString &name, const QString &description = "")
{
    q.addBindValue(name);
    q.addBindValue(description);
    q.exec();
    return q.lastInsertId();
}

void addEmployeeSkill(QSqlQuery &q, const QVariant employee_id, const QVariant skill_id)
{
    q.addBindValue(employee_id);
    q.addBindValue(skill_id);
    q.exec();
}

QVariant addEmployer(QSqlQuery &q, const QString &name, const QString &company_name,
                     const QVariant location, const QString phonenumber)
{
    q.addBindValue(name);
    q.addBindValue(company_name);
    q.addBindValue(location);
    q.addBindValue(phonenumber);
    q.exec();
    return q.lastInsertId();
}

QVariant addOpenPosition(QSqlQuery &q, const QVariant employer_id, const QString title,
                         const QString description, const QVariant location,
                         const QDate from_date, const QDate to_date)
{
    q.addBindValue(employer_id);
    q.addBindValue(title);
    q.addBindValue(description);
    q.addBindValue(location);
    q.addBindValue(from_date);
    q.addBindValue(to_date);
    q.exec();
    return q.lastInsertId();
}

void addRequiredSkill(QSqlQuery &q, const QVariant position_id, const QVariant skill_id)
{
    q.addBindValue(position_id);
    q.addBindValue(skill_id);
    q.exec();
}

QVariant addLocation(QSqlQuery &q, const QString &name, const QVariant parent = 0)
{
    q.addBindValue(name);
    q.addBindValue(parent);
    q.exec();
    return q.lastInsertId();
}

QSqlError initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./uicdb.sqlite");
    qDebug() << QCoreApplication::applicationDirPath();

    if (!db.open())
        return db.lastError();

    QStringList tables = db.tables();
    if (tables.contains("employees", Qt::CaseInsensitive)
        && tables.contains("skills", Qt::CaseInsensitive)
        && tables.contains("employeeskills", Qt::CaseInsensitive)
        && tables.contains("employers", Qt::CaseInsensitive)
        && tables.contains("openpositions", Qt::CaseInsensitive)
        && tables.contains("requiredskills", Qt::CaseInsensitive)
        && tables.contains("images", Qt::CaseInsensitive)
        && tables.contains("locations", Qt::CaseInsensitive))
        return QSqlError();

    QSqlQuery q;
    if (!q.exec(QLatin1String("create table employees(id integer primary key, name varchar, birthdate date, area integer, phonenumber varchar)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table skills(id integer primary key, name varchar, description text)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table employeeskills(id integer primary key, employee_id integer, skill_id integer)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table employers(id integer primary key, name varchar, company_name varchar, location integer, phonenumber varchar)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table openpositions(id integer primary key, employer_id integer, title varchar, description text, location integer, from_date date, to_date date)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table requiredskills(id integer primary key, position_id integer, skill_id integer)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table images(id integer primary key, employee_id integer, employer_id integer, image blob)")))
        return q.lastError();
    if (!q.exec(QLatin1String("create table locations(id integer primary key, name text, parent integer)")))
        return q.lastError();

    if (!q.prepare(QLatin1String("insert into locations(name, parent) values(?, ?)")))
        return q.lastError();
    QVariant windhoek = addLocation(q, QLatin1String("Windhoek"));
    QVariant havana = addLocation(q, QLatin1String("Havana"), windhoek);

    if (!q.prepare(QLatin1String("insert into employees(name, birthdate, area, phonenumber) values(?, ?, ?, ?)")))
        return q.lastError();
    QVariant janesmith = addEmployee(q, QLatin1String("Jane Smith"), QDate(1991, 12, 9), havana, QLatin1String("+264 40 123 1234"));

    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615686300','Hosea Kutako','1993-07-04',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615586123','Kaire Mbuende','1992-02-09',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615586570','Michelle McLean','1994-12-12',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264618716400','Bridget Pickering','1995-05-20',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615511400','Behati Prinsloo','1996-08-31',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264611138642','Hulda Shipanga','1990-09-19',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615500431','Nahas Angula','1991-04-17',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615435151','Hage Geingob','1992-03-13',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615990012','Theo-Ben Gurirab','1993-08-14',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615958947','Katuutire Kaura','1994-01-01',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264614903241','Fanuel Kozonguizi','1995-10-03',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615432410','Nangolo Mbumba','1996-05-26',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615999912','Dirk Mudge','1990-04-28',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615500001','Sam Nujoma','1991-03-12',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264618829148','Hifikepunye Pohamba','1992-02-23',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264615721890','Ngarikutuke Tjiriange 34178','1985-03-03',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264616179411','Ben Ulenga','1994-05-30',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264614449101','Hendrik Witbooi','1995-06-14',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264619883195','Immanuel Ngatjizeko','1996-02-20',2);");
    q.exec("insert into employees(phonenumber, name, birthdate, area) values ('+264614870177','Bernard Esau','1990-09-15',2);");

/*    if (!q.prepare(QLatin1String("insert into skills(name, description) values(?, ?)")))
        return q.lastError();
    QVariant java = addSkill(q, QLatin1String("Java programming"));
*/
    q.exec("insert into skills(name) values('Child care)");
    q.exec("insert into skills(name) values('Graphic design)");
    q.exec("insert into skills(name) values('Car repair)");
    q.exec("insert into skills(name) values('PHP)");
    q.exec("insert into skills(name) values('Writing)");
    q.exec("insert into skills(name) values('Metalwork)");
    q.exec("insert into skills(name) values('English)");
    q.exec("insert into skills(name) values('C++)");
    q.exec("insert into skills(name) values('Building)");
    q.exec("insert into skills(name) values('CSS)");
    q.exec("insert into skills(name) values('Composing)");
    q.exec("insert into skills(name) values('Woodwork)");
    q.exec("insert into skills(name) values('Java)");
    q.exec("insert into skills(name) values('Usability)");
    q.exec("insert into skills(name) values('HTML)");
    q.exec("insert into skills(name) values('Assembler)");
    q.exec("insert into skills(name) values('Gardening)");
    q.exec("insert into skills(name) values('French)");
    q.exec("insert into skills(name) values('Cleaning)");
    q.exec("insert into skills(name) values('User interface design)");
    q.exec("insert into skills(name) values('Accounting)");
    q.exec("insert into skills(name) values('Javascript)");
    q.exec("insert into skills(name) values('Guitar)");
    q.exec("insert into skills(name) values('Nursing)");
    q.exec("insert into skills(name) values('Handicrafts)");
    q.exec("insert into skills(name) values('Watch repair)");

    q.exec("insert into employeeskills(employee_id, skill_id) values(1,1)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(1,2)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(2,3)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(2,4)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(2,5)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(3,6)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(3,7)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(4,8)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(4,9)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(5,10)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(5,11)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(5,12)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(6,13)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(6,14)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(6,15)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(7,16)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(7,17)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(8,18)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(9,19)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(9,20)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(9,21)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(9,22)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(10,23)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(11,24)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(11,25)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(11,26)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(12,26)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(12,24)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(12,22)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(12,20)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(12,18)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(13,16)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(13,14)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(13,12)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(13,10)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(14,8)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(15,6)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(16,4)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(17,2)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(18,1)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(19,3)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(19,6)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(19,9)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(19,12)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(20,14)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(20,15)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(21,16)");
    q.exec("insert into employeeskills(employee_id, skill_id) values(21,17)");

    if (!q.prepare(QLatin1String("insert into employeeskills(employee_id, skill_id) values(?, ?)")))
        return q.lastError();
    addEmployeeSkill(q, janesmith, java);

    return QSqlError();
}

#endif // INITDB_H
