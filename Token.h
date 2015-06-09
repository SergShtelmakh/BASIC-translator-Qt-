/*!
 * \file Token.h
 * \date 2015/04/24
 *
 * \author SergShtelmakh
 * Contact: sh.serg1993@gmail.com
 *
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <QPoint>
#include <QString>
#include <QHash>
#include "Expression.h"

/*!
 * @brief This class used to store informations about tokens.
 */
class Identifier;
class Token
{

public:

    /*!
     * @brief This enumerate include tokens category.
     */
    enum TokenCategory {
        categoryNone            = 0,    //!< Incorrect token.
        categoryCharToken       = 1,    //!< Character token (e.g. +, -, *, / ...).
        categoryIdentifier      = 2,    //!< Identifier (e.g. var1, var2 ...).
        categoryKeyword         = 3,    //!< Keyword (e.g. int, bool, double ...).
        categoryLineFeed        = 4,    //!< Line feed.
        categoryNumberLiteral   = 5,    //!< Number literal (e.g. 5.54, 48.21E-45 ...).
        categorySpace           = 6,    //!< Space token.
        categoryStringLiteral   = 7     //!< String litaral (e.g. "literal1", "literal2" ...).
    };

    Token(){}
    Token(const Token &other);
    Token(const QString &lexeme, TokenCategory category, const QString &errorInformation = "", const QPoint &position = QPoint(), Expression::Type type = Expression::NONE);

    Token& operator=(const Token& newToken);

    QString lexeme() const;

    TokenCategory category() const;

    QString errorInformation() const;

    void setPosition(const QPoint &value);
    QPoint position() const;

    QString getAllErrorInformation() const;

    /*!
     * This method used to check is token correct.
     *
     * @return If token is correct returns true other returns false.
     */
    bool isCorrect() const;

    static TokenCategory stringToTokenCategory(const QString &string);

    Identifier *identifier() const;
    void setIdentifier(Identifier *identifier);

    Expression::Type type() const;
    void setType(const Expression::Type &type);

private:

    QString m_lexeme;               //!< Tokens lexeme.
    TokenCategory m_tokenCategory;  //!< Tokens category.
    QString m_errorInformation;     //!< Tokens error information.
    QPoint m_position;              //!< Tokens position.
    Identifier *m_identifier;
    Expression::Type m_type;


    static QHash <QString, TokenCategory> m_convertingStringToTokenCategoryHash;

};

QString MakeStringRepresentation(const Token &token);
int GetTokenLineNumber(const Token &token);
int GetOperationPriority(const Token &token);
bool isOperation(const Token &token);
bool isLogicalOperation(const Token &token);
Expression::Type resultType(const Token &operation, const Token &first, const Token &second);

#endif // TOKEN_H
