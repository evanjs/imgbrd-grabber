type Iterable<T> = T[] | { [k: number]: T } | { [k: string]: T };

interface ITag {
    id?: number;
    name: string;
    count?: number;
    type?: string;
    typeId?: number;
}
interface IImage {
    file_url: string;
}
interface IPool {
    id?: number;
    name: string;
    previous?: number;
    current?: number;
    next?: number;
}

interface IUrl {
    url: string;
    headers?: { [key: string]: string };
}

interface IError {
    error: string;
}
interface IParsedSearch {
    images: Iterable<IImage>;
    tags?: Iterable<ITag>;
    wiki?: string;
}
interface IParsedTags {
    tags: Iterable<ITag>;
}
interface IParsedDetails {
    pools?: Iterable<IPool>;
    tags?: Iterable<ITag>;
    imageUrl?: string;
    createdAt?: string;
}

type IAuthField = IAuthNormalField | IAuthHashField;
interface IAuthFieldBase {
    key: string;
}
interface IAuthNormalField extends IAuthFieldBase {
    type: "username" | "password";
}
interface IAuthHashField extends IAuthFieldBase {
    type: "hash";
    hash: "md5" | "sha1";
    salt: string;
}

type IAuthCheck = IAuthCheckCookie;
interface IAuthCheckCookie {
    type: "cookie";
    key: string;
}

interface IAuth {
    type: string;
    fields: IAuthField[];
    check?: IAuthCheck;
    [name: string]: any;
}

interface IApi {
    name: string;
    auth: string[];
    maxLimit: number;
    search: {
        url: (query: any, opts: any, previous: any) => IUrl | IError | string;
        parse: (src: string) => IParsedSearch;
    };
    details?: {
        url: (id: number, md5: string) => IUrl | IError | string;
        parse: (src: string) => IParsedDetails;
    };
    tags?: {
        url: (query: any, opts: any) => IUrl | IError | string;
        parse: (src: string) => IParsedTags;
    };
}
interface ISource {
    name: string;
    modifiers?: string[];
    auth?: { [id: string]: IAuth };
    apis: { [id: string]: IApi };
}

declare let __source: ISource;
declare const Grabber: any;