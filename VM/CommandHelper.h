DEF_CMD(ADD, 10, 0,
{
int tmp = stack.Pop();
int tmp2 = stack.Pop();
stack.Push( tmp + tmp2 );
}
)


DEF_CMD(SUB, 11, 0,
{
int tmp = stack.Pop();
int tmp2 = stack.Pop();
stack.Push( tmp2 - tmp );
}
)

DEF_CMD(MUL, 12, 0,
{
int tmp = stack.Pop();
int tmp2 = stack.Pop();
stack.Push( tmp * tmp2 );
}
)

DEF_CMD(DIV, 13, 0,
{
int tmp = stack.Pop();
int tmp2 = stack.Pop();
stack.Push( tmp2 / tmp );
}
)

DEF_CMD(PUSH, 30, 1,
{
stack.Push( *args );
}
)

DEF_CMD(PUSHR, 31, 1,
{
switch( *args ){
case 1:
stack.Push(rax);
break;
case 2:
stack.Push(rbx);
break;
case 3:
stack.Push(rcx);
break;
case 4:
stack.Push(rdx);
break;
}
}
)

DEF_CMD(POP, 40, 1,
{
switch( *args ){
case 1:
rax = stack.Pop();
break;
case 2:
rbx = stack.Pop();
break;
case 3:
rcx = stack.Pop();
break;
case 4:
rdx = stack.Pop();
break;
}
}
)

DEF_CMD(OUT, 50, 0,
{
std::cout<<stack.Top()<< "\n";
}
)

DEF_CMD(IN, 60, 0,
{
int in;
std::cin >> in;
stack.Push(in);
}
)


DEF_CMD(DATA, 250, 0, {
})

DEF_CMD(STOP, 251, 0, {
})


DEF_CMD(END, 255, 0, {
isEnd = true;
})

DEF_CMD(LABEL, 254, 1, {
})

DEF_CMD(PRINT, 253, 1, {
const char* ptr = handler.GetPointer( args[0] );
int size = *reinterpret_cast<const int*>( ptr );
//std::cout<<"(( "<<size << "\n";
const char* str = ptr + 4;
for( int i = 0; i < size; ++i ) {
std::cout<<*( str + i );
}
std::cout<<"\n";
}
)

DEF_CMD(JMP, 70, 1,
{
handler.SetIp( *args );
}
)

DEF_CMD(JE, 71, 1,
{
int tmp1 = stack.Pop();
int tmp2 = stack.Pop();
if( tmp1 == tmp2 ) {
handler.SetIp( *args );
}
}
)

DEF_CMD(JA, 72, 1,
{
int tmp1 = stack.Pop();
int tmp2 = stack.Pop();
if( tmp1 > tmp2 ) {
handler.SetIp( *args );
}
}
)


DEF_CMD(JB, 73, 1,
{
int tmp1 = stack.Pop();
int tmp2 = stack.Pop();
if( tmp1 < tmp2 ) {
handler.SetIp( *args );
}
}
)

DEF_CMD(CALL, 80, 1,
{
retStack.Push( handler.GetIp() );
handler.SetIp( *args );

}
)

DEF_CMD(RET, 85, 0,
{
int nextIp = retStack.Pop();
handler.SetIp( nextIp );
}
)

DEF_CMD(STR, 200, 0,
{}
)

