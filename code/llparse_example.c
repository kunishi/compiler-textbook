int lookahead; /* $B8=:_$N%H!<%/%s(B */
int nexttoken(); /* $B<!$N%H!<%/%s$rJV$9(B */

/* $B@aE@(B n $B$K%H!<%/%s(B t $B$r;R$H$7$FDI2C(B */
void addChild(node n, int t);
/* $B@aE@(B n $B$N:G=i$N;R$rJV$9(B */
node firstChild(node n);
/* $B@aE@(B child $B$N<!$NDo$rJV$9(B */
node nextSibling(node n);

void match(int t)
{
  if (lookahead == t) {
    lookahead = nexttoken();
  } else {
    /* $B9=J8%(%i!<(B */
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
    /* $B9=J8%(%i!<(B */
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
    /* $B9=J8%(%i!<(B */
  }
}
