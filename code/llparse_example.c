int lookahead; /* 現在のトークン */
int nexttoken(); /* 次のトークンを返す */

/* 節点 n にトークン t を子として追加 */
void addChild(node n, int t);
/* 節点 n の最初の子を返す */
node firstChild(node n);
/* 節点 child の次の弟を返す */
node nextSibling(node n);

void match(int t)
{
  if (lookahead == t) {
    lookahead = nexttoken();
  } else {
    /* 構文エラー */
  }
}

void type(node n)
{
  node child;
  if (lookahead == INTEGER || lookahead == CHAR
      || lookahead == NUM) {
    addChild(n, simple);
    child = firstChild(n);
    simple(child);
  } else if (lookahead == HAT) {
    addChild(n, HAT);
    addChild(n, ID);
    child = firstChild(n);
    match(HAT, child);
    child = nextSibling(child);
    match(ID, child);
  } else if (lookahead == ARRAY) {
    addChild(n, ARRAY);
    addChild(n, LPAREN);
    addChild(n, simple);
    addChild(n, RPAREN);
    addChild(n, OF);
    addChild(n, type);

    child = firstChild(n);
    match(ARRAY, child);
    child = nextSibling(child);
    match(LPAREN);
    child = nextSibling(child);
    simple(child);
    child = nextSibling(child);
    match(RPAREN);
    child = nextSibling(child);
    match(OF);
    child = nextSibling(child);
    type(child);
  } else {
    /* 構文エラー */
  }
}

void simple(node n)
{
  node child;
  if (lookahead == INTEGER) {
    addChild(n, INTEGER);
    child = firstChild(n);
    match(INTEGER, child);
  } else if (lookahead == CHAR) {
    addChild(n, CHAR);
    child = firstChild(n);
    match(CHAR, child);
  } else if (lookahead == NUM) {
    addChild(n, NUM);
    addChild(n, DOTDOT);
    addChild(n, NUM);
    child = firstChild(n);
    match(NUM);
    child = nextSibling(child);
    match(DOTDOT);
    child = nextSibling(child);
    match(NUM);
  } else {
    /* 構文エラー */
  }
}
