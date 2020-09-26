template<typename It, typename Tag>
It advance_impl(It it, int n, Tag tag) {
    for (int i = 0; i < n; ++i)
        ++it;
    return it;
}

template<typename It>
It advance_impl(It it, int n, std::random_access_iterator_tag tag) {
    return it + n;
}

template<typename It>
It advance(It it, int n) {
    return advance_impl(it, n, typename It::iterator_category());
}
