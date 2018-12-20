#include <QCoreApplication>
#include <QTextStream>

//#define DEBUG

const int MAXLEN = 26;

QTextStream cout(stdout);
QTextStream cin(stdin);

bool convertPos(QString str, int length, int *x, int *y) {
    if (str.length() < 2) {
        cout << QString("Неправильная запись") << endl;
        return false;
    }
    QChar xletter = str.at(0).toUpper();
    if (xletter < 'A' || xletter > 'Z') {
        cout << QString("Неверна буква") << endl;
        return false;
    }
    int ix = xletter.unicode() - 'A' + 1;
    bool ok;
    int iy = str.mid(1).toInt(&ok);
    if (!ok || iy <= 0) {
        cout << QString("Неверное число") << endl;
        return false;
    }
    if (ix > length || iy > length) {
        cout << QString("Слишком большая координата") << endl;
        return false;
    }
    *x = ix - 1;
    *y = iy - 1;
    return true;
}

int xmove(int move) {
    switch (move) {
        case 0:
        case 7:
            return 2;

        case 1:
        case 6:
            return 1;

        case 2:
        case 5:
            return -1;

        case 3:
        case 4:
            return -2;
    }

    return 0;
}

int ymove(int move) {
    switch (move) {
        case 0:
        case 3:
            return -1;

        case 1:
        case 2:
            return -2;

        case 4:
        case 7:
            return 1;

        case 5:
        case 6:
            return 2;
    }

    return 0;
}

int main()
{
    int depth = 0;
    int startx;
    int starty;
    int endx;
    int endy;

    int length = 0;
    cout << QString("Введите длину стороны поля (максимум 26): ") << flush;
    cin >> length;
    if (length > MAXLEN || length < 1) {
        cout << QString("Ошибка") << endl;
        return 1;
    }

    QString startpos;
    cout << QString("Введите начальную позицию коня: ") << flush;
    cin >> startpos;
    if (!convertPos(startpos, length, &endx, &endy))
        return 1;

    QString endpos;
    cout << QString("Введите искомую позицию: ") << flush;
    cin >> endpos;
    if (!convertPos(endpos, length, &startx, &starty))
        return 1;

    int board[MAXLEN][MAXLEN];

    for (int y = 0; y < length; y++) {
        for (int x = 0; x < length; x++) {
            board[y][x] = -1;
        }
    }
    board[starty][startx] = 0;

    bool found = (startx == endx && starty == endy);
    bool changed = true;
    while (!found && changed) {
        changed = false;
        depth++;
        for (int y = 0; y < length && !found; y++) {
            for (int x = 0; x < length && !found; x++) {
                if (board[y][x] != depth - 1)
                    continue;
                for (int move = 0; move < 8; move++) {
                    int newx = x + xmove(move);
                    int newy = y + ymove(move);
                    if (newx == endx && newy == endy) {
                        found = true;
                        break;
                    }
                    if (newx < 0 || newy < 0 || newx >= length || newy >= length) {
                        continue;
                    }
                    if (board[newy][newx] != - 1)
                        continue;
                    changed = true;
                    board[newy][newx] = depth;
                }
            }
        }
    }

    if (!found) {
        cout << QString("Внутренняя ошибка #1; путь не найден") << endl;
        return 1;
    }

#ifdef DEBUG
    for (int y = 0; y < length; y++) {
        for (int x = 0; x < length; x++) {
            cout << QString::number(board[y][x]).leftJustified(4, ' ') << " ";
        }
        cout << endl;
    }
#endif

    int x = endx;
    int y = endy;
    for (int i = depth - 1; i >= 0; i--) {
        bool found = false;
        cout << QString(QChar('A' + x)) + QString::number(y + 1) << " > ";
        for (int move = 0; move < 8; move++) {
            int newx = x + xmove(move);
            int newy = y + ymove(move);
            if (newx < 0 || newy < 0 || newx >= length || newy >= length) {
                continue;
            }
            if (board[newy][newx] == i) {
                x = newx;
                y = newy;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << QString("Внутренняя ошибка #2; путь не найден") << endl;
            return 1;
        }
    }
    cout << QString(QChar('A' + startx)) + QString::number(starty + 1) << endl;

    return 0;
}
