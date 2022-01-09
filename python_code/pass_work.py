def get_pass_work(path_file):
    '''
    return string
    '''
    with open(path_file) as f:
        c_pass_work, p_pass_work = f.readlines()
        p_pass_work = p_pass_work.rstrip("\n")
        c_pass_work = c_pass_work.rstrip("\n")

    return p_pass_work, c_pass_work

if __name__ == "__main__": 
    p, c = get_pass_work("passwork.txt")
    print(c, p)