namespace px
{
    namespace math
    {
        template<typename type>type percent(type i, int percentage) {return px::math::percent<type>(i,percentage,1);} //! percent without accuracy bool
        template<typename inputType,typename returnType>returnType sqrRoot(inputType input){return px::math::nRoot<inputType,returnType>(input, 2);} //! sqrRoot
    }
}