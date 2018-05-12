
int main()
{
    NostraEngine &engine;
    NostraEngine::setActiveInstance(*(NostraEngine::createInstance()));
    engine = NostraEngine::get();


    return 0;
}